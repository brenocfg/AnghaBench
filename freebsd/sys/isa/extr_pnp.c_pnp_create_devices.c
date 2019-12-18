#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint32_t ;
typedef  int u_char ;
struct pnp_set_config_arg {int csn; int ldn; } ;
struct TYPE_3__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  vendor_id; } ;
typedef  TYPE_1__ pnp_id ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ BUS_ADD_CHILD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int FALSE ; 
 int ISACFGATTR_CANDISABLE ; 
 int ISACFGATTR_DYNAMIC ; 
 int /*<<< orphan*/  ISA_ORDER_PNP ; 
 int /*<<< orphan*/  ISA_SET_CONFIG_CALLBACK (scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct pnp_set_config_arg*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ PNP_LRES_NUM (int) ; 
 scalar_t__ PNP_RES_TYPE (int) ; 
 int PNP_SRES_LEN (int) ; 
 int PNP_SRES_NUM (int) ; 
#define  PNP_TAG_END 129 
 scalar_t__ PNP_TAG_ID_ANSI ; 
#define  PNP_TAG_LOGICAL_DEVICE 128 
 int /*<<< orphan*/  bcopy (int*,char*,int) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*) ; 
 int /*<<< orphan*/  device_set_desc_copy (scalar_t__,char*) ; 
 int /*<<< orphan*/  isa_set_configattr (scalar_t__,int) ; 
 int /*<<< orphan*/  isa_set_logicalid (scalar_t__,char) ; 
 int /*<<< orphan*/  isa_set_pnp_csn (scalar_t__,int) ; 
 int /*<<< orphan*/  isa_set_pnp_ldn (scalar_t__,int) ; 
 int /*<<< orphan*/  isa_set_serial (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_set_vendorid (scalar_t__,int /*<<< orphan*/ ) ; 
 struct pnp_set_config_arg* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_check_quirks (int /*<<< orphan*/ ,char,int,int /*<<< orphan*/ *) ; 
 char* pnp_eisaformat (char) ; 
 int /*<<< orphan*/  pnp_parse_resources (scalar_t__,int*,int,int) ; 
 int /*<<< orphan*/  pnp_set_config ; 

__attribute__((used)) static int
pnp_create_devices(device_t parent, pnp_id *p, int csn,
    u_char *resources, int len)
{
	u_char tag, *resp, *resinfo, *startres = NULL;
	int large_len, scanning = len, retval = FALSE;
	uint32_t logical_id;
	device_t dev = 0;
	int ldn = 0;
	struct pnp_set_config_arg *csnldn;
	char buf[100];
	char *desc = NULL;

	resp = resources;
	while (scanning > 0) {
		tag = *resp++;
		scanning--;
		if (PNP_RES_TYPE(tag) != 0) {
			/* Large resource */
			if (scanning < 2) {
				scanning = 0;
				continue;
			}
			large_len = resp[0] + (resp[1] << 8);
			resp += 2;

			if (scanning < large_len) {
				scanning = 0;
				continue;
			}
			resinfo = resp;
			resp += large_len;
			scanning -= large_len;

			if (PNP_LRES_NUM(tag) == PNP_TAG_ID_ANSI) {
				if (dev) {
					/*
					 * This is an optional device
					 * identifier string. Skip it
					 * for now.
					 */
					continue;
				}
				/* else mandately card identifier string */
				if (large_len > sizeof(buf) - 1)
					large_len = sizeof(buf) - 1;
				bcopy(resinfo, buf, large_len);

				/*
				 * Trim trailing spaces.
				 */
				while (buf[large_len-1] == ' ')
					large_len--;
				buf[large_len] = '\0';
				desc = buf;
				continue;
			}

			continue;
		}
		
		/* Small resource */
		if (scanning < PNP_SRES_LEN(tag)) {
			scanning = 0;
			continue;
		}
		resinfo = resp;
		resp += PNP_SRES_LEN(tag);
		scanning -= PNP_SRES_LEN(tag);
			
		switch (PNP_SRES_NUM(tag)) {
		case PNP_TAG_LOGICAL_DEVICE:
			/*
			 * Parse the resources for the previous
			 * logical device (if any).
			 */
			if (startres) {
				pnp_parse_resources(dev, startres,
				    resinfo - startres - 1, ldn);
				dev = 0;
				startres = NULL;
			}

			/* 
			 * A new logical device. Scan for end of
			 * resources.
			 */
			bcopy(resinfo, &logical_id, 4);
			pnp_check_quirks(p->vendor_id, logical_id, ldn, NULL);
			dev = BUS_ADD_CHILD(parent, ISA_ORDER_PNP, NULL, -1);
			if (desc)
				device_set_desc_copy(dev, desc);
			else
				device_set_desc_copy(dev,
				    pnp_eisaformat(logical_id));
			isa_set_vendorid(dev, p->vendor_id);
			isa_set_serial(dev, p->serial);
			isa_set_logicalid(dev, logical_id);
			isa_set_configattr(dev,
			    ISACFGATTR_CANDISABLE | ISACFGATTR_DYNAMIC);
			csnldn = malloc(sizeof *csnldn, M_DEVBUF, M_NOWAIT);
			if (!csnldn) {
				device_printf(parent, "out of memory\n");
				scanning = 0;
				break;
			}
			csnldn->csn = csn;
			csnldn->ldn = ldn;
			ISA_SET_CONFIG_CALLBACK(parent, dev, pnp_set_config,
			    csnldn);
			isa_set_pnp_csn(dev, csn);
			isa_set_pnp_ldn(dev, ldn);
			ldn++;
			startres = resp;
			break;
		    
		case PNP_TAG_END:
			if (!startres) {
				device_printf(parent, "malformed resources\n");
				scanning = 0;
				break;
			}
			pnp_parse_resources(dev, startres,
			    resinfo - startres - 1, ldn);
			dev = 0;
			startres = NULL;
			scanning = 0;
			break;

		default:
			/* Skip this resource */
			break;
		}
	}

	return (retval);
}
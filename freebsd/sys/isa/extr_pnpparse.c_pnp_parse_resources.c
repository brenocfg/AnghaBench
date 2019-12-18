#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_char ;
struct isa_config {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int I16 (int*) ; 
 int /*<<< orphan*/  ISA_ADD_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct isa_config*) ; 
 int MAXDEP ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ PNP_RES_TYPE (int) ; 
 int PNP_SRES_LEN (int) ; 
 int PNP_SRES_NUM (int) ; 
#define  PNP_TAG_END 130 
#define  PNP_TAG_END_DEPENDANT 129 
#define  PNP_TAG_START_DEPENDANT 128 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  bzero (struct isa_config*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct isa_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_get_logicalid (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pnp_merge_resources (int /*<<< orphan*/ ,struct isa_config*,struct isa_config*) ; 
 int /*<<< orphan*/  pnp_parse_dependant (int /*<<< orphan*/ ,int*,int,struct isa_config*,int) ; 
 scalar_t__ pnp_parse_desc (int /*<<< orphan*/ ,int,int*,int,struct isa_config*,int) ; 
 int /*<<< orphan*/  pnp_printf (int /*<<< orphan*/ ,char*,...) ; 

void
pnp_parse_resources(device_t dev, u_char *resources, int len, int ldn)
{
	struct isa_config *configs;
	struct isa_config *config;
	device_t parent;
	int priorities[1 + MAXDEP];
	u_char *start;
	u_char *p;
	u_char tag;
	u_int32_t id;
	int ncfgs;
	int l;
	int i;

	parent = device_get_parent(dev);
	id = isa_get_logicalid(dev);

	configs = (struct isa_config *)malloc(sizeof(*configs)*(1 + MAXDEP),
					      M_DEVBUF, M_NOWAIT | M_ZERO);
	if (configs == NULL) {
		device_printf(parent, "No memory to parse PNP data\n");
		return;
	}
	config = &configs[0];
	priorities[0] = 0;
	ncfgs = 1;

	p = resources;
	start = NULL;
	while (len > 0) {
		tag = *p++;
		len--;
		if (PNP_RES_TYPE(tag) == 0) {
			/* Small resource */
			l = PNP_SRES_LEN(tag);
			if (len < l) {
				len = 0;
				continue;
			}
			len -= l;

			switch (PNP_SRES_NUM(tag)) {

			case PNP_TAG_START_DEPENDANT:
				if (start != NULL) {
					/*
					 * Copy the common resources first,
					 * then parse the "dependent" resources.
					 */
					pnp_merge_resources(dev, &configs[0],
							    config);
					pnp_parse_dependant(dev, start,
							    p - start - 1,
							    config, ldn);
				}
				start = p + l;
				if (ncfgs > MAXDEP) {
					device_printf(parent, "too many dependent configs (%d)\n", MAXDEP);
					len = 0;
					break;
				}
				config = &configs[ncfgs];
				/*
				 * If the priority is not specified,
				 * then use the default of 'acceptable'
				 */
				if (l > 0)
					priorities[ncfgs] = p[0];
				else
					priorities[ncfgs] = 1;
				if (bootverbose)
					pnp_printf(id, "start dependent (%d)\n",
						   priorities[ncfgs]);
				ncfgs++;
				break;

			case PNP_TAG_END_DEPENDANT:
				if (start == NULL) {
					device_printf(parent,
						      "malformed resources\n");
					len = 0;
					break;
				}
				/*
				 * Copy the common resources first,
				 * then parse the "dependent" resources.
				 */
				pnp_merge_resources(dev, &configs[0], config);
				pnp_parse_dependant(dev, start, p - start - 1,
						    config, ldn);
				start = NULL;
				if (bootverbose)
					pnp_printf(id, "end dependent\n");
				/*
				 * Back to the common part; clear it
				 * as its contents has already been copied
				 * to each dependent.
				 */
				config = &configs[0];
				bzero(config, sizeof(*config));
				break;

			case PNP_TAG_END:
				if (start != NULL) {
					device_printf(parent,
						      "malformed resources\n");
				}
				len = 0;
				break;

			default:
				if (start != NULL)
					/* defer parsing a dependent section */
					break;
				if (pnp_parse_desc(dev, tag, p, l, config, ldn))
					len = 0;
				break;
			}
			p += l;
		} else {
			/* Large resource */
			if (len < 2) {
				len = 0;
				break;
			}
			l = I16(p);
			p += 2;
			len -= 2;
			if (len < l) {
				len = 0;
				break;
			}
			len -= l;
			if (start == NULL &&
			    pnp_parse_desc(dev, tag, p, l, config, ldn)) {
				len = 0;
				break;
			}
			p += l;
		}
	}

	if (ncfgs == 1) {
		/* Single config without dependants */
		ISA_ADD_CONFIG(parent, dev, priorities[0], &configs[0]);
		free(configs, M_DEVBUF);
		return;
	}

	for (i = 1; i < ncfgs; i++) {
		/*
		 * Merge the remaining part of the common resources,
		 * if any. Strictly speaking, there shouldn't be common/main
		 * resources after the END_DEPENDENT tag.
		 */
		pnp_merge_resources(dev, &configs[0], &configs[i]);
		ISA_ADD_CONFIG(parent, dev, priorities[i], &configs[i]);
	}

	free(configs, M_DEVBUF);
}
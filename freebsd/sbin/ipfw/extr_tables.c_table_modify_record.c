#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xi ;
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tent ;
struct TYPE_22__ {int /*<<< orphan*/  flags; } ;
struct TYPE_23__ {char* tablename; int result; TYPE_2__ head; int /*<<< orphan*/  vmask; void* type; } ;
typedef  TYPE_3__ ipfw_xtable_info ;
typedef  TYPE_3__ ipfw_obj_tentry ;
struct TYPE_21__ {void* type; int /*<<< orphan*/  name; } ;
struct TYPE_24__ {TYPE_1__ ntlv; } ;
typedef  TYPE_5__ ipfw_obj_header ;

/* Variables and functions */
#define  EACCES 140 
#define  EEXIST 139 
#define  EFBIG 138 
#define  ENOENT 137 
#define  ESRCH 136 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IPFW_TF_UPDATE ; 
#define  IPFW_TR_ADDED 135 
#define  IPFW_TR_DELETED 134 
#define  IPFW_TR_ERROR 133 
#define  IPFW_TR_EXISTS 132 
#define  IPFW_TR_IGNORED 131 
#define  IPFW_TR_LIMIT 130 
#define  IPFW_TR_NOTFOUND 129 
#define  IPFW_TR_UPDATED 128 
 int IP_FW_TABLE_XADD ; 
 int IP_FW_TABLE_XDEL ; 
 TYPE_3__* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_do_create (TYPE_5__*,TYPE_3__*) ; 
 int table_do_modify_record (int,TYPE_5__*,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  table_show_entry (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  tentry_fill_key (TYPE_5__*,TYPE_3__*,char*,int,void**,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  tentry_fill_value (TYPE_5__*,TYPE_3__*,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static void
table_modify_record(ipfw_obj_header *oh, int ac, char *av[], int add,
    int quiet, int update, int atomic)
{
	ipfw_obj_tentry *ptent, tent, *tent_buf;
	ipfw_xtable_info xi;
	uint8_t type;
	uint32_t vmask;
	int cmd, count, error, i, ignored;
	char *texterr, *etxt, *px;

	if (ac == 0)
		errx(EX_USAGE, "address required");
	
	if (add != 0) {
		cmd = IP_FW_TABLE_XADD;
		texterr = "Adding record failed";
	} else {
		cmd = IP_FW_TABLE_XDEL;
		texterr = "Deleting record failed";
	}

	/*
	 * Calculate number of entries:
	 * Assume [key val] x N for add
	 * and
	 * key x N for delete
	 */
	count = (add != 0) ? ac / 2 + 1 : ac;

	if (count <= 1) {
		/* Adding single entry with/without value */
		memset(&tent, 0, sizeof(tent));
		tent_buf = &tent;
	} else {
		
		if ((tent_buf = calloc(count, sizeof(tent))) == NULL)
			errx(EX_OSERR,
			    "Unable to allocate memory for all entries");
	}
	ptent = tent_buf;

	memset(&xi, 0, sizeof(xi));
	count = 0;
	while (ac > 0) {
		tentry_fill_key(oh, ptent, *av, add, &type, &vmask, &xi);

		/*
		 * Compatibility layer: auto-create table if not exists.
		 */
		if (xi.tablename[0] == '\0') {
			xi.type = type;
			xi.vmask = vmask;
			strlcpy(xi.tablename, oh->ntlv.name,
			    sizeof(xi.tablename));
			if (quiet == 0)
				warnx("DEPRECATED: inserting data into "
				    "non-existent table %s. (auto-created)",
				    xi.tablename);
			table_do_create(oh, &xi);
		}
	
		oh->ntlv.type = type;
		ac--; av++;
	
		if (add != 0 && ac > 0) {
			tentry_fill_value(oh, ptent, *av, type, vmask);
			ac--; av++;
		}

		if (update != 0)
			ptent->head.flags |= IPFW_TF_UPDATE;

		count++;
		ptent++;
	}

	error = table_do_modify_record(cmd, oh, tent_buf, count, atomic);

	/*
	 * Compatibility stuff: do not yell on duplicate keys or
	 * failed deletions.
	 */
	if (error == 0 || (error == EEXIST && add != 0) ||
	    (error == ENOENT && add == 0)) {
		if (quiet != 0) {
			if (tent_buf != &tent)
				free(tent_buf);
			return;
		}
	}

	/* Report results back */
	ptent = tent_buf;
	for (i = 0; i < count; ptent++, i++) {
		ignored = 0;
		switch (ptent->result) {
		case IPFW_TR_ADDED:
			px = "added";
			break;
		case IPFW_TR_DELETED:
			px = "deleted";
			break;
		case IPFW_TR_UPDATED:
			px = "updated";
			break;
		case IPFW_TR_LIMIT:
			px = "limit";
			ignored = 1;
			break;
		case IPFW_TR_ERROR:
			px = "error";
			ignored = 1;
			break;
		case IPFW_TR_NOTFOUND:
			px = "notfound";
			ignored = 1;
			break;
		case IPFW_TR_EXISTS:
			px = "exists";
			ignored = 1;
			break;
		case IPFW_TR_IGNORED:
			px = "ignored";
			ignored = 1;
			break;
		default:
			px = "unknown";
			ignored = 1;
		}

		if (error != 0 && atomic != 0 && ignored == 0)
			printf("%s(reverted): ", px);
		else
			printf("%s: ", px);

		table_show_entry(&xi, ptent);
	}

	if (tent_buf != &tent)
		free(tent_buf);

	if (error == 0)
		return;
	/* Get real OS error */
	error = errno;

	/* Try to provide more human-readable error */
	switch (error) {
	case EEXIST:
		etxt = "record already exists";
		break;
	case EFBIG:
		etxt = "limit hit";
		break;
	case ESRCH:
		etxt = "table not found";
		break;
	case ENOENT:
		etxt = "record not found";
		break;
	case EACCES:
		etxt = "table is locked";
		break;
	default:
		etxt = strerror(error);
	}

	errx(EX_OSERR, "%s: %s", texterr, etxt);
}
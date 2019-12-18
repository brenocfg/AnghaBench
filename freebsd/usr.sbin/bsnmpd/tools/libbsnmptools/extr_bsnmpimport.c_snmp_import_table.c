#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snmp_toolinfo {int dummy; } ;
struct snmp_oid2str {int /*<<< orphan*/  var; int /*<<< orphan*/  strlen; struct snmp_index_entry* string; } ;
struct snmp_index_entry {struct snmp_index_entry* string; int /*<<< orphan*/  index_list; int /*<<< orphan*/  var; int /*<<< orphan*/  strlen; } ;
struct enum_pairs {int dummy; } ;
typedef  int int32_t ;
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;
struct TYPE_2__ {int /*<<< orphan*/  lno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_INDEX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_INDEXES_MAX ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int TOK_BITS ; 
 int TOK_DEFTYPE ; 
 int TOK_ENUM ; 
 int TOK_STR ; 
 int TOK_TYPE ; 
 int /*<<< orphan*/  asn_append_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct snmp_index_entry* calloc (int,int) ; 
 int /*<<< orphan*/  enum_pairs_free (struct enum_pairs*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct snmp_index_entry*) ; 
 int gettoken (struct snmp_toolinfo*) ; 
 TYPE_1__* input ; 
 int parse_type (struct snmp_toolinfo*,int*,int*,struct enum_pairs**) ; 
 int /*<<< orphan*/  snmp_import_update_table (int /*<<< orphan*/ ,struct snmp_index_entry*) ; 
 int /*<<< orphan*/  snmp_index_listfree (int /*<<< orphan*/ *) ; 
 scalar_t__ snmp_syntax_insert (int /*<<< orphan*/ *,struct enum_pairs*,int,int) ; 
 int snmp_table_insert (struct snmp_toolinfo*,struct snmp_index_entry*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
snmp_import_table(struct snmp_toolinfo *snmptoolctx, struct snmp_oid2str *obj)
{
	int32_t i, tok;
	enum snmp_tc tc;
	struct snmp_index_entry *entry;

	if ((entry = calloc(1, sizeof(struct snmp_index_entry))) == NULL) {
		syslog(LOG_ERR, "malloc() failed: %s", strerror(errno));
		return (-1);
	}

	STAILQ_INIT(&(entry->index_list));

	for (i = 0, tok = gettoken(snmptoolctx); i < SNMP_INDEXES_MAX; i++) {
		int32_t syntax;
		struct enum_pairs *enums = NULL;

		if (tok != TOK_TYPE && tok != TOK_DEFTYPE && tok != TOK_ENUM &&
		    tok != TOK_BITS)
			break;

		if ((syntax = parse_type(snmptoolctx, &tok, &tc, &enums)) < 0) {
			enum_pairs_free(enums);
			snmp_index_listfree(&(entry->index_list));
			free(entry);
			return (-1);
		}

		if (snmp_syntax_insert(&(entry->index_list), enums, syntax,
		    tc) < 0) {
			snmp_index_listfree(&(entry->index_list));
			enum_pairs_free(enums);
			free(entry);
			return (-1);
		}
	}

	if (i == 0 || i > SNMP_INDEXES_MAX) {
		warnx("Bad number of indexes at line %d", input->lno);
		snmp_index_listfree(&(entry->index_list));
		free(entry);
		return (-1);
	}

	if (tok != TOK_STR) {
		warnx("String expected after indexes at line %d", input->lno);
		snmp_index_listfree(&(entry->index_list));
		free(entry);
		return (-1);
	}

	entry->string = obj->string;
	entry->strlen = obj->strlen;
	asn_append_oid(&(entry->var), &(obj->var));

	if ((i = snmp_table_insert(snmptoolctx, entry)) < 0) {
		snmp_index_listfree(&(entry->index_list));
		free(entry);
		return (-1);
	} else if (i == 0) {
		/* Same entry already present in lists. */
		free(entry->string);
		free(entry);
		return (0);
	}

	(void) snmp_import_update_table(ENTRY_INDEX, entry);

	return (1);
}
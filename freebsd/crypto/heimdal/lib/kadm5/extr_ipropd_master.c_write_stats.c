#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct TYPE_5__ {char* name; int flags; struct TYPE_5__* next; int /*<<< orphan*/  seen; scalar_t__ version; TYPE_1__ addr; } ;
typedef  TYPE_2__ slave ;
typedef  int /*<<< orphan*/ * rtbl_t ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_address ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RTBL_ALIGN_RIGHT ; 
 int /*<<< orphan*/  SLAVE_ADDRESS ; 
 int SLAVE_F_DEAD ; 
 int /*<<< orphan*/  SLAVE_NAME ; 
 int /*<<< orphan*/  SLAVE_SEEN ; 
 int /*<<< orphan*/  SLAVE_STATUS ; 
 int /*<<< orphan*/  SLAVE_VERSION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ krb5_format_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_print_address (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_sockaddr2address (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_add_column (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_add_column_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * rtbl_create () ; 
 int /*<<< orphan*/  rtbl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtbl_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtbl_set_column_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtbl_set_prefix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
write_stats(krb5_context context, slave *slaves, uint32_t current_version)
{
    char str[100];
    rtbl_t tbl;
    time_t t = time(NULL);
    FILE *fp;

    fp = open_stats(context);
    if (fp == NULL)
	return;

    krb5_format_time(context, t, str, sizeof(str), TRUE);
    fprintf(fp, "Status for slaves, last updated: %s\n\n", str);

    fprintf(fp, "Master version: %lu\n\n", (unsigned long)current_version);

    tbl = rtbl_create();
    if (tbl == NULL) {
	fclose(fp);
	return;
    }

    rtbl_add_column(tbl, SLAVE_NAME, 0);
    rtbl_add_column(tbl, SLAVE_ADDRESS, 0);
    rtbl_add_column(tbl, SLAVE_VERSION, RTBL_ALIGN_RIGHT);
    rtbl_add_column(tbl, SLAVE_STATUS, 0);
    rtbl_add_column(tbl, SLAVE_SEEN, 0);

    rtbl_set_prefix(tbl, "  ");
    rtbl_set_column_prefix(tbl, SLAVE_NAME, "");

    while (slaves) {
	krb5_address addr;
	krb5_error_code ret;
	rtbl_add_column_entry(tbl, SLAVE_NAME, slaves->name);
	ret = krb5_sockaddr2address (context,
				     (struct sockaddr*)&slaves->addr.sa, &addr);
	if(ret == 0) {
	    krb5_print_address(&addr, str, sizeof(str), NULL);
	    krb5_free_address(context, &addr);
	    rtbl_add_column_entry(tbl, SLAVE_ADDRESS, str);
	} else
	    rtbl_add_column_entry(tbl, SLAVE_ADDRESS, "<unknown>");

	snprintf(str, sizeof(str), "%u", (unsigned)slaves->version);
	rtbl_add_column_entry(tbl, SLAVE_VERSION, str);

	if (slaves->flags & SLAVE_F_DEAD)
	    rtbl_add_column_entry(tbl, SLAVE_STATUS, "Down");
	else
	    rtbl_add_column_entry(tbl, SLAVE_STATUS, "Up");

	ret = krb5_format_time(context, slaves->seen, str, sizeof(str), TRUE);
	rtbl_add_column_entry(tbl, SLAVE_SEEN, str);

	slaves = slaves->next;
    }

    rtbl_format(tbl, fp);
    rtbl_destroy(tbl);

    fclose(fp);
}
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
struct sbuf {int dummy; } ;
struct TYPE_2__ {char* value; char* val; } ;

/* Variables and functions */
 size_t PACKAGESITE ; 
 TYPE_1__* c ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sbuf_bcat (struct sbuf*,char const*,int) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char const*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void
subst_packagesite(const char *abi)
{
	struct sbuf *newval;
	const char *variable_string;
	const char *oldval;

	if (c[PACKAGESITE].value != NULL)
		oldval = c[PACKAGESITE].value;
	else
		oldval = c[PACKAGESITE].val;

	if ((variable_string = strstr(oldval, "${ABI}")) == NULL)
		return;

	newval = sbuf_new_auto();
	sbuf_bcat(newval, oldval, variable_string - oldval);
	sbuf_cat(newval, abi);
	sbuf_cat(newval, variable_string + strlen("${ABI}"));
	sbuf_finish(newval);

	free(c[PACKAGESITE].value);
	c[PACKAGESITE].value = strdup(sbuf_data(newval));
}
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
struct TYPE_5__ {char** optv; int flag; int optc; struct TYPE_5__* next; TYPE_1__* module; } ;
typedef  TYPE_2__ pam_chain_t ;
struct TYPE_4__ {char* path; } ;

/* Variables and functions */
 int PAM_BUF_ERR ; 
 int PAM_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isprint (unsigned char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 

int
openpam_dump_chain(const char *name, pam_chain_t *chain)
{
	char *modname, **opt, *p;
	int i;

	for (i = 0; chain != NULL; ++i, chain = chain->next) {
		/* declare the module's struct pam_module */
		modname = strrchr(chain->module->path, '/');
		modname = strdup(modname ? modname : chain->module->path);
		if (modname == NULL)
			return (PAM_BUF_ERR);
		for (p = modname; *p && *p != '.'; ++p)
			/* nothing */ ;
		*p = '\0';
		printf("extern struct pam_module %s_pam_module;\n", modname);
		/* module arguments */
		printf("static char *%s_%d_optv[] = {\n", name, i);
		for (opt = chain->optv; *opt; ++opt) {
			printf("\t\"");
			for (p = *opt; *p; ++p) {
				if (isprint((unsigned char)*p) && *p != '"')
					printf("%c", *p);
				else
					printf("\\x%02x", (unsigned char)*p);
			}
			printf("\",\n");
		}
		printf("\tNULL,\n");
		printf("};\n");
		/* next module in chain */
		if (chain->next != NULL)
			printf("static pam_chain_t %s_%d;\n", name, i + 1);
		/* chain entry */
		printf("static pam_chain_t %s_%d = {\n", name, i);
		printf("\t.module = &%s_pam_module,\n", modname);
		printf("\t.flag = 0x%08x,\n", chain->flag);
		printf("\t.optc = %d,\n", chain->optc);
		printf("\t.optv = %s_%d_optv,\n", name, i);
		if (chain->next)
			printf("\t.next = &%s_%d,\n", name, i + 1);
		else
			printf("\t.next = NULL,\n");
		printf("};\n");
		free(modname);
	}
	return (PAM_SUCCESS);
}
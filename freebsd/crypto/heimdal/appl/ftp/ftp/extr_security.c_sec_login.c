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
struct sec_client_mech {char* name; scalar_t__ (* init ) (void*) ;int (* auth ) (void*,char*) ;scalar_t__ size; } ;

/* Variables and functions */
 int AUTH_CONTINUE ; 
 int AUTH_OK ; 
 int CONTINUE ; 
 int ERROR ; 
 void* app_data ; 
 int code ; 
 int command (char*,char*) ; 
 void* command_prot ; 
 scalar_t__ doencrypt ; 
 struct sec_client_mech* mech ; 
 struct sec_client_mech** mechs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* prot_private ; 
 void* prot_safe ; 
 void* realloc (void*,scalar_t__) ; 
 void* request_data_prot ; 
 int sec_complete ; 
 scalar_t__ stub1 (void*) ; 
 int stub2 (void*,char*) ; 
 int verbose ; 
 int /*<<< orphan*/  warnx (char*,unsigned long) ; 

int
sec_login(char *host)
{
    int ret;
    struct sec_client_mech **m;
    int old_verbose = verbose;

    verbose = -1; /* shut up all messages this will produce (they
		     are usually not very user friendly) */

    for(m = mechs; *m && (*m)->name; m++) {
	void *tmp;

	tmp = realloc(app_data, (*m)->size);
	if (tmp == NULL) {
	    warnx ("realloc %lu failed", (unsigned long)(*m)->size);
	    return -1;
	}
	app_data = tmp;

	if((*m)->init && (*(*m)->init)(app_data) != 0) {
	    printf("Skipping %s...\n", (*m)->name);
	    continue;
	}
	printf("Trying %s...\n", (*m)->name);
	ret = command("AUTH %s", (*m)->name);
	if(ret != CONTINUE){
	    if(code == 504){
		printf("%s is not supported by the server.\n", (*m)->name);
	    }else if(code == 534){
		printf("%s rejected as security mechanism.\n", (*m)->name);
	    }else if(ret == ERROR) {
		printf("The server doesn't support the FTP "
		       "security extensions.\n");
		verbose = old_verbose;
		return -1;
	    }
	    continue;
	}

	ret = (*(*m)->auth)(app_data, host);

	if(ret == AUTH_CONTINUE)
	    continue;
	else if(ret != AUTH_OK){
	    /* mechanism is supposed to output error string */
	    verbose = old_verbose;
	    return -1;
	}
	mech = *m;
	sec_complete = 1;
	if(doencrypt) {
	    command_prot = prot_private;
	    request_data_prot = prot_private;
	} else {
	    command_prot = prot_safe;
	}
	break;
    }

    verbose = old_verbose;
    return *m == NULL;
}
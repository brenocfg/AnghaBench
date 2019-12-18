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
typedef  int /*<<< orphan*/  message ;

/* Variables and functions */
 int client_setup (int /*<<< orphan*/ *,int*,char**) ; 
 int /*<<< orphan*/  context ; 
 int doit (char*,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/ * get_default_username () ; 
 int /*<<< orphan*/ * remote_name ; 
 int /*<<< orphan*/  service ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

int
main(int argc, char **argv)
{
    int argcc,port,i;
    int ret=0;

    argcc = argc;
    port = client_setup(&context, &argcc, argv);

    if (remote_name == NULL) {
	remote_name = get_default_username ();
	if (remote_name == NULL)
	    errx (1, "who are you?");
    }

    for (i = argcc;i < argc; i++) {
	char message[128];
	ret = doit (argv[i], port, service, message, sizeof(message));
	if(ret == 0)
	    warnx ("%s: ok", argv[i]);
	else
	    warnx ("%s: failed: %s", argv[i], message);
    }
    return(ret);
}
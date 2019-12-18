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
struct helper_data {char** argv; int /*<<< orphan*/  fd; int /*<<< orphan*/  buf; int /*<<< orphan*/  pre_data; int /*<<< orphan*/  (* pre_exec ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  err ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int execvp_noalloc (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int helper_child(void *arg)
{
	struct helper_data *data = arg;
	char **argv = data->argv;
	int err, ret;

	if (data->pre_exec != NULL)
		(*data->pre_exec)(data->pre_data);
	err = execvp_noalloc(data->buf, argv[0], argv);

	/* If the exec succeeds, we don't get here */
	CATCH_EINTR(ret = write(data->fd, &err, sizeof(err)));

	return 0;
}
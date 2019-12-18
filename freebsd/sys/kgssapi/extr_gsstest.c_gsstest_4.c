#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_6__ {int rpc_gss_error; int system_error; } ;
typedef  TYPE_1__ rpc_gss_error_t ;
struct TYPE_7__ {int program; int version; int /*<<< orphan*/  callback; } ;
typedef  TYPE_2__ rpc_gss_callback_t ;
typedef  int /*<<< orphan*/  principal ;
typedef  int /*<<< orphan*/  SVCPOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_INDEFINITE ; 
 int /*<<< orphan*/  getcredhostname (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*,int,int) ; 
 int /*<<< orphan*/  rpc_gss_clear_callback (TYPE_2__*) ; 
 int /*<<< orphan*/  rpc_gss_clear_svc_name (int,int) ; 
 int /*<<< orphan*/  rpc_gss_get_error (TYPE_1__*) ; 
 char** rpc_gss_get_mechanisms () ; 
 int /*<<< orphan*/  rpc_gss_set_callback (TYPE_2__*) ; 
 int /*<<< orphan*/  rpc_gss_set_svc_name (char*,char const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  server_new_context ; 
 int /*<<< orphan*/  server_program_1 ; 
 int /*<<< orphan*/  svc_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_run (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svcpool_create (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcpool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gsstest_4(struct thread *td)
{
	SVCPOOL *pool;
	char principal[128 + 5];
	const char **mechs;
	static rpc_gss_callback_t cb;

	memcpy(principal, "host@", 5);
	getcredhostname(td->td_ucred, principal + 5, sizeof(principal) - 5);

	mechs = rpc_gss_get_mechanisms();
	while (*mechs) {
		if (!rpc_gss_set_svc_name(principal, *mechs, GSS_C_INDEFINITE,
			123456, 1)) {
			rpc_gss_error_t e;

			rpc_gss_get_error(&e);
			printf("setting name for %s for %s failed: %d, %d\n",
			    principal, *mechs,
			    e.rpc_gss_error, e.system_error);
		}
		mechs++;
	}

	cb.program = 123456;
	cb.version = 1;
	cb.callback = server_new_context;
	rpc_gss_set_callback(&cb);

	pool = svcpool_create("gsstest", NULL);

	svc_create(pool, server_program_1, 123456, 1, NULL);
	svc_run(pool);

	rpc_gss_clear_svc_name(123456, 1);
	rpc_gss_clear_callback(&cb);

	svcpool_destroy(pool);

	return (0);
}
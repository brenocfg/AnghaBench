#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct gsstest_args {int a_op; int /*<<< orphan*/  a_res; int /*<<< orphan*/  a_args; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/  value; } ;
struct gsstest_2_res {TYPE_2__ output_token; int /*<<< orphan*/  min_stat; int /*<<< orphan*/  maj_stat; int /*<<< orphan*/  step; TYPE_1__ input_token; } ;
struct gsstest_2_args {TYPE_2__ output_token; int /*<<< orphan*/  min_stat; int /*<<< orphan*/  maj_stat; int /*<<< orphan*/  step; TYPE_1__ input_token; } ;
typedef  int /*<<< orphan*/  res ;
struct TYPE_9__ {int length; struct gsstest_2_res* value; } ;
typedef  TYPE_3__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyin (int /*<<< orphan*/ ,struct gsstest_2_res*,int) ; 
 int copyout (struct gsstest_2_res*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int gsstest_1 (struct thread*) ; 
 int /*<<< orphan*/  gsstest_2 (struct thread*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int gsstest_3 (struct thread*) ; 
 int gsstest_4 (struct thread*) ; 
 struct gsstest_2_res* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gsstest(struct thread *td, struct gsstest_args *uap)
{
	int error;

	switch (uap->a_op) {
	case 1:
                return (gsstest_1(td));

	case 2: {
		struct gsstest_2_args args;
		struct gsstest_2_res res;
		gss_buffer_desc input_token, output_token;
		OM_uint32 junk;

		error = copyin(uap->a_args, &args, sizeof(args));
		if (error)
			return (error);
		input_token.length = args.input_token.length;
		input_token.value = malloc(input_token.length, M_GSSAPI,
		    M_WAITOK);
		error = copyin(args.input_token.value, input_token.value,
		    input_token.length);
		if (error) {
			gss_release_buffer(&junk, &input_token);
			return (error);
		}
		output_token.length = 0;
		output_token.value = NULL;
		gsstest_2(td, args.step, &input_token,
		    &res.maj_stat, &res.min_stat, &output_token);
		gss_release_buffer(&junk, &input_token);
		if (output_token.length > args.output_token.length) {
			gss_release_buffer(&junk, &output_token);
			return (EOVERFLOW);
		}
		res.output_token.length = output_token.length;
		res.output_token.value = args.output_token.value;
		error = copyout(output_token.value, res.output_token.value,
		    output_token.length);
		gss_release_buffer(&junk, &output_token);
		if (error)
			return (error);

		return (copyout(&res, uap->a_res, sizeof(res)));
		
		break;
	}
	case 3:
		return (gsstest_3(td));
	case 4:
		return (gsstest_4(td));
	}

        return (EINVAL);
}
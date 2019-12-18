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
struct print_s {int /*<<< orphan*/  verbose; int /*<<< orphan*/  counter; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  print_certificate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
print_f(hx509_context hxcontext, void *ctx, hx509_cert cert)
{
    struct print_s *s = ctx;

    printf("cert: %d\n", s->counter++);
    print_certificate(context, cert, s->verbose);

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
struct TYPE_3__ {int num_strings; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ getarg_strings ;

/* Variables and functions */
 int hx509_certs_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
certs_strings(hx509_context contextp, const char *type, hx509_certs certs,
	      hx509_lock lock, const getarg_strings *s)
{
    int i, ret;

    for (i = 0; i < s->num_strings; i++) {
	ret = hx509_certs_append(contextp, certs, lock, s->strings[i]);
	if (ret)
	    hx509_err(contextp, 1, ret,
		      "hx509_certs_append: %s %s", type, s->strings[i]);
    }
}
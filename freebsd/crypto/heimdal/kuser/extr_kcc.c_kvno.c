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
struct kvno_options {int /*<<< orphan*/  enctype_string; int /*<<< orphan*/  cache_string; } ;
struct kgetcred_options {int /*<<< orphan*/  enctype_string; int /*<<< orphan*/  cache_string; } ;
typedef  int /*<<< orphan*/  k ;

/* Variables and functions */
 int kgetcred (struct kgetcred_options*,int,char**) ; 
 int /*<<< orphan*/  memset (struct kgetcred_options*,int /*<<< orphan*/ ,int) ; 

int
kvno(struct kvno_options *opt, int argc, char **argv)
{
    struct kgetcred_options k;
    memset(&k, 0, sizeof(k));

    k.cache_string = opt->cache_string;
    k.enctype_string = opt->enctype_string;

    return kgetcred(&k, argc, argv);
}
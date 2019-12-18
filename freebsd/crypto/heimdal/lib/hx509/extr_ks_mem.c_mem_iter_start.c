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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long* malloc (int) ; 

__attribute__((used)) static int
mem_iter_start(hx509_context context,
	       hx509_certs certs,
	       void *data,
	       void **cursor)
{
    unsigned long *iter = malloc(sizeof(*iter));

    if (iter == NULL)
	return ENOMEM;

    *iter = 0;
    *cursor = iter;

    return 0;
}
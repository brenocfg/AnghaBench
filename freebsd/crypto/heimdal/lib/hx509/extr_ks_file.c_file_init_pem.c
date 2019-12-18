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
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  USE_PEM ; 
 int file_init_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
file_init_pem(hx509_context context,
	      hx509_certs certs, void **data, int flags,
	      const char *residue, hx509_lock lock)
{
    return file_init_common(context, certs, data, flags, residue, lock, USE_PEM);
}
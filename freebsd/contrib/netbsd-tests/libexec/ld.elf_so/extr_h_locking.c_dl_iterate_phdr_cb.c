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
struct dl_phdr_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  tls_callback_sym () ; 

__attribute__((used)) static int
dl_iterate_phdr_cb(struct dl_phdr_info *info, size_t size, void *data)
{
	(*tls_callback_sym)();
	return 0;
}
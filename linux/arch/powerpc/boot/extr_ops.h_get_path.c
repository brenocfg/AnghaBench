#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* (* get_path ) (void const*,char*,int) ;} ;

/* Variables and functions */
 TYPE_1__ dt_ops ; 
 char* stub1 (void const*,char*,int) ; 

__attribute__((used)) static inline char *get_path(const void *phandle, char *buf, int len)
{
	if (dt_ops.get_path)
		return dt_ops.get_path(phandle, buf, len);

	return NULL;
}
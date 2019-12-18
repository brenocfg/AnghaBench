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
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 struct sockaddr_dl* malloc (size_t,int /*<<< orphan*/ ,int) ; 

struct sockaddr_dl *
link_alloc_sdl(size_t size, int flags)
{

	return (malloc(size, M_TEMP, flags));
}
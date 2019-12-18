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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sockaddr *sockaddr_dup(const void *data, socklen_t len)
{
	struct sockaddr *ret = (struct sockaddr *)malloc(len);
	memcpy(ret, data, len);
	return ret;
}
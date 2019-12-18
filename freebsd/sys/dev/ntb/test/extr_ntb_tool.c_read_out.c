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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ubuf ;
struct sysctl_req {int dummy; } ;

/* Variables and functions */
 int SYSCTL_OUT (struct sysctl_req*,char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_out(struct sysctl_req *req, uint64_t val)
{
	char ubuf[16];

	memset((void *)ubuf, 0, sizeof(ubuf));
	snprintf(ubuf, sizeof(ubuf), "0x%jx", val);

	return SYSCTL_OUT(req, ubuf, sizeof(ubuf));
}
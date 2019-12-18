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
struct crypt_find_op {int crid; char const* name; } ;
typedef  int /*<<< orphan*/  find ;

/* Variables and functions */
 int /*<<< orphan*/  CIOCFINDDEV ; 
 int /*<<< orphan*/  bzero (struct crypt_find_op*,int) ; 
 int /*<<< orphan*/  devcrypto () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypt_find_op*) ; 

__attribute__((used)) static const char *
crfind(int crid)
{
	static struct crypt_find_op find;

	bzero(&find, sizeof(find));
	find.crid = crid;
	if (ioctl(devcrypto(), CIOCFINDDEV, &find) == -1)
		err(1, "ioctl(CIOCFINDDEV)");
	return find.name;
}
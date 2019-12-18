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
typedef  int /*<<< orphan*/  uint_t ;
struct inode_data {int dummy; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  inode_release_if_exist (struct inode_data*) ; 
 int sockaddr_read_bind (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sockaddr_read(addr_t sockaddr_addr, void *sockaddr, uint_t *sockaddr_len) {
    struct inode_data *inode = NULL;
    int err = sockaddr_read_bind(sockaddr_addr, sockaddr, sockaddr_len, NULL);
    inode_release_if_exist(inode);
    return err;
}
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
typedef  int /*<<< orphan*/  bytes ;
struct TYPE_2__ {int (* encode ) (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  app_data ; 
 int /*<<< orphan*/  block_write (int,void*,int) ; 
 int /*<<< orphan*/  data_prot ; 
 int /*<<< orphan*/  free (void*) ; 
 int htonl (int) ; 
 TYPE_1__* mech ; 
 int /*<<< orphan*/  ntohl (int) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int
sec_send(int fd, char *from, int length)
{
    int bytes;
    void *buf;
    bytes = (*mech->encode)(app_data, from, length, data_prot, &buf);
    bytes = htonl(bytes);
    block_write(fd, &bytes, sizeof(bytes));
    block_write(fd, buf, ntohl(bytes));
    free(buf);
    return length;
}
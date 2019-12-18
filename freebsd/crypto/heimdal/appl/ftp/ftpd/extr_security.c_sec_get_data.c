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
struct buffer {int* data; scalar_t__ index; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  len ;
struct TYPE_2__ {int /*<<< orphan*/  (* decode ) (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  app_data ; 
 int block_read (int,int*,int) ; 
 int /*<<< orphan*/  data_prot ; 
 TYPE_1__* mech ; 
 int ntohl (int) ; 
 void* realloc (int*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sec_get_data(int fd, struct buffer *buf, int level)
{
    int len;
    int b;
    void *tmp;

    b = block_read(fd, &len, sizeof(len));
    if (b == 0)
	return 0;
    else if (b < 0)
	return -1;
    len = ntohl(len);
    tmp = realloc(buf->data, len);
    if (tmp == NULL)
	return -1;
    buf->data = tmp;
    b = block_read(fd, buf->data, len);
    if (b == 0)
	return 0;
    else if (b < 0)
	return -1;
    buf->size = (*mech->decode)(app_data, buf->data, len, data_prot);
    buf->index = 0;
    return 0;
}
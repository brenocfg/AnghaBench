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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEE (char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static uint32_t
cvt(const void *src, int size, char swap)
{
    uint32_t ret = 0;
    if (size != 2 && size != 4) {
	EEE("Invalid size %d\n", size);
	exit(1);
    }
    memcpy(&ret, src, size);
    if (swap) {
	unsigned char tmp, *data = (unsigned char *)&ret;
	int i;
        for (i = 0; i < size / 2; i++) {
            tmp = data[i];
            data[i] = data[size - (1 + i)];
            data[size - (1 + i)] = tmp;
        }
    }
    return ret;
}
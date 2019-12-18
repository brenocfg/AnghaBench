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

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 

char* mac2str(unsigned char* mac) {
        static char ret[6*3];

        sprintf(ret, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

        return ret;
}
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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline const char*
decoration_as_sgr(uint8_t decoration) {
    switch(decoration) {
        case 1: return "4;";
        case 2: return "4:2;";
        case 3: return "4:3;";
        default: return "24;";
    }
}
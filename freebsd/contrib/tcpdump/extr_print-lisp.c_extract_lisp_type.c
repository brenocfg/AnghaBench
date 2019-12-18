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
 int TYPE_INDEX ; 

__attribute__((used)) static inline uint8_t extract_lisp_type(uint8_t lisp_hdr_flags)
{
	return (lisp_hdr_flags) >> TYPE_INDEX;
}
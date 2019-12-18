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
 scalar_t__ quote_path_fully ; 
 scalar_t__* sq_lookup ; 

__attribute__((used)) static inline int sq_must_quote(char c)
{
	return sq_lookup[(unsigned char)c] + quote_path_fully > 0;
}
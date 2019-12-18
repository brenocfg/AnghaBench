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
typedef  int /*<<< orphan*/  uint8_t ;
struct hashfile {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  hashwrite (struct hashfile*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void hashwrite_u8(struct hashfile *f, uint8_t data)
{
	hashwrite(f, &data, sizeof(data));
}
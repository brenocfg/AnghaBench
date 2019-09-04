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
struct hashfile {int dummy; } ;
struct ewah_bitmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ ewah_serialize_to (struct ewah_bitmap*,int /*<<< orphan*/ ,struct hashfile*) ; 
 int /*<<< orphan*/  hashwrite_ewah_helper ; 

__attribute__((used)) static inline void dump_bitmap(struct hashfile *f, struct ewah_bitmap *bitmap)
{
	if (ewah_serialize_to(bitmap, hashwrite_ewah_helper, f) < 0)
		die("Failed to write bitmap index");
}
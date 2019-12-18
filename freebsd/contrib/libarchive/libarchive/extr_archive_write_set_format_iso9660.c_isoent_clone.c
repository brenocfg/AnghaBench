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
struct isoent {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 struct isoent* isoent_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct isoent *
isoent_clone(struct isoent *src)
{
	return (isoent_new(src->file));
}
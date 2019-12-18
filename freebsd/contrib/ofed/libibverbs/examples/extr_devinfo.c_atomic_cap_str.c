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
typedef  enum ibv_atomic_cap { ____Placeholder_ibv_atomic_cap } ibv_atomic_cap ;

/* Variables and functions */
#define  IBV_ATOMIC_GLOB 130 
#define  IBV_ATOMIC_HCA 129 
#define  IBV_ATOMIC_NONE 128 

__attribute__((used)) static const char *atomic_cap_str(enum ibv_atomic_cap atom_cap)
{
	switch (atom_cap) {
	case IBV_ATOMIC_NONE: return "ATOMIC_NONE";
	case IBV_ATOMIC_HCA:  return "ATOMIC_HCA";
	case IBV_ATOMIC_GLOB: return "ATOMIC_GLOB";
	default:              return "invalid atomic capability";
	}
}
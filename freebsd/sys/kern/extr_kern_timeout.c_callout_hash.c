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
typedef  int u_int ;
typedef  int sbintime_t ;

/* Variables and functions */
 int CC_HASH_SHIFT ; 

__attribute__((used)) static inline u_int
callout_hash(sbintime_t sbt)
{

	return (sbt >> (32 - CC_HASH_SHIFT));
}
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
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int callout_hash (int /*<<< orphan*/ ) ; 
 int callwheelmask ; 

__attribute__((used)) static inline u_int
callout_get_bucket(sbintime_t sbt)
{

	return (callout_hash(sbt) & callwheelmask);
}
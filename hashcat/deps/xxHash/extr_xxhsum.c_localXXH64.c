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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  XXH64 (void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static U32 localXXH64(const void* buffer, size_t bufferSize, U32 seed) { return (U32)XXH64(buffer, bufferSize, seed); }
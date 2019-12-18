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
typedef  int /*<<< orphan*/  ISzAllocPtr ;

/* Variables and functions */
 void* BigAlloc (size_t) ; 
 int /*<<< orphan*/  UNUSED_VAR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *SzBigAlloc(ISzAllocPtr p, size_t size) { UNUSED_VAR(p); return BigAlloc(size); }
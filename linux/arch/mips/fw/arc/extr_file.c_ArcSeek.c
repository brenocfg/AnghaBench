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
struct linux_bigint {int dummy; } ;
typedef  enum linux_seekmode { ____Placeholder_linux_seekmode } linux_seekmode ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_CALL3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct linux_bigint*,int) ; 
 int /*<<< orphan*/  seek ; 

LONG
ArcSeek(ULONG FileID, struct linux_bigint *Position, enum linux_seekmode SeekMode)
{
	return ARC_CALL3(seek, FileID, Position, SeekMode);
}
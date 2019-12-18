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
typedef  int /*<<< orphan*/  uint64_t ;
struct archive_read {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_le64dec (int /*<<< orphan*/  const*) ; 
 scalar_t__ consume (struct archive_read*,int) ; 
 int /*<<< orphan*/  read_ahead (struct archive_read*,int,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int read_u64(struct archive_read* a, uint64_t* pvalue) {
	const uint8_t* p;
	if(!read_ahead(a, 8, &p))
		return 0;

	*pvalue = archive_le64dec(p);
	return ARCHIVE_OK == consume(a, 8) ? 1 : 0;
}
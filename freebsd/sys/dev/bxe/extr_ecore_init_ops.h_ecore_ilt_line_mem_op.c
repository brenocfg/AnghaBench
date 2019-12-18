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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ilt_line {int /*<<< orphan*/  size; int /*<<< orphan*/  page; int /*<<< orphan*/  page_mapping; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ILT_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_ILT_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ILT_MEMOP_FREE ; 

__attribute__((used)) static int ecore_ilt_line_mem_op(struct bxe_softc *sc,
				 struct ilt_line *line, uint32_t size, uint8_t memop)
{
	if (memop == ILT_MEMOP_FREE) {
		ECORE_ILT_FREE(line->page, line->page_mapping, line->size);
		return 0;
	}
	ECORE_ILT_ZALLOC(line->page, &line->page_mapping, size);
	if (!line->page)
		return -1;
	line->size = size;
	return 0;
}
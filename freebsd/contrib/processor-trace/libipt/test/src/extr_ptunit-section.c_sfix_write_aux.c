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
struct section_fixture {int /*<<< orphan*/  file; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 size_t fwrite (int /*<<< orphan*/  const*,int,size_t,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (size_t,size_t) ; 

__attribute__((used)) static struct ptunit_result sfix_write_aux(struct section_fixture *sfix,
					   const uint8_t *buffer, size_t size)
{
	size_t written;

	written = fwrite(buffer, 1, size, sfix->file);
	ptu_uint_eq(written, size);

	fflush(sfix->file);

	return ptu_passed();
}
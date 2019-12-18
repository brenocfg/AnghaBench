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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t const u32 ;
typedef  int /*<<< orphan*/  ostream_t ;
typedef  int /*<<< orphan*/  istream_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORRUPTION () ; 
 int /*<<< orphan*/ * IO_get_read_ptr (int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/ * IO_get_write_ptr (int /*<<< orphan*/ * const,size_t const) ; 
 size_t const IO_istream_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,size_t const) ; 

__attribute__((used)) static u32 copy_literals(const size_t literal_length, istream_t *litstream,
                         ostream_t *const out) {
    // If the sequence asks for more literals than are left, the
    // sequence must be corrupted
    if (literal_length > IO_istream_len(litstream)) {
        CORRUPTION();
    }

    u8 *const write_ptr = IO_get_write_ptr(out, literal_length);
    const u8 *const read_ptr =
         IO_get_read_ptr(litstream, literal_length);
    // Copy literals to output
    memcpy(write_ptr, read_ptr, literal_length);

    return literal_length;
}
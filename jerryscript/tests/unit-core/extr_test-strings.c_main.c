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
typedef  int /*<<< orphan*/  valid_utf8_string_1 ;
typedef  int lit_utf8_size_t ;
typedef  int const lit_utf8_byte_t ;
typedef  int /*<<< orphan*/  invalid_cesu8_string_3 ;
typedef  int /*<<< orphan*/  invalid_cesu8_string_2 ;
typedef  int /*<<< orphan*/  invalid_cesu8_string_1 ;
typedef  int /*<<< orphan*/  ecma_string_t ;
typedef  size_t ecma_length_t ;
typedef  scalar_t__ ecma_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  ecma_deref_ecma_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_finalize () ; 
 int /*<<< orphan*/  ecma_init () ; 
 int /*<<< orphan*/ * ecma_new_ecma_string_from_utf8 (int const*,int) ; 
 size_t ecma_string_get_length (int /*<<< orphan*/ *) ; 
 size_t generate_cesu8_string (int const*,int) ; 
 int /*<<< orphan*/  jmem_finalize () ; 
 int /*<<< orphan*/  jmem_init () ; 
 int lit_code_unit_to_utf8 (int,int const*) ; 
 int lit_is_valid_cesu8_string (int const*,int) ; 
 int /*<<< orphan*/  lit_utf8_decr (int const**) ; 
 int /*<<< orphan*/  lit_utf8_incr (int const**) ; 
 scalar_t__ lit_utf8_peek_next (int const*) ; 
 scalar_t__ lit_utf8_peek_prev (int const*) ; 
 scalar_t__ lit_utf8_read_next (int const**) ; 
 scalar_t__ lit_utf8_read_prev (int const**) ; 
 size_t lit_utf8_string_length (int const*,int) ; 
 int max_bytes_in_string ; 
 int max_code_units_in_string ; 
 int rand () ; 
 int test_iters ; 
 int test_subiters ; 

int
main (void)
{
  TEST_INIT ();

  jmem_init ();
  ecma_init ();

  lit_utf8_byte_t cesu8_string[max_bytes_in_string];
  ecma_char_t code_units[max_code_units_in_string];
  const lit_utf8_byte_t *saved_positions[max_code_units_in_string];

  for (int i = 0; i < test_iters; i++)
  {
    lit_utf8_size_t cesu8_string_size = (i == 0) ? 0 : (lit_utf8_size_t) (rand () % max_bytes_in_string);
    ecma_length_t length = generate_cesu8_string (cesu8_string, cesu8_string_size);

    ecma_string_t *char_collection_string_p = ecma_new_ecma_string_from_utf8 (cesu8_string, cesu8_string_size);
    ecma_length_t char_collection_len = ecma_string_get_length (char_collection_string_p);
    TEST_ASSERT (char_collection_len == length);
    ecma_deref_ecma_string (char_collection_string_p);

    TEST_ASSERT (lit_utf8_string_length (cesu8_string, cesu8_string_size) == length);

    const lit_utf8_byte_t *curr_p = cesu8_string;
    const lit_utf8_byte_t *end_p = cesu8_string + cesu8_string_size;

    ecma_length_t calculated_length = 0;
    ecma_length_t code_units_count = 0;

    while (curr_p < end_p)
    {
      code_units[code_units_count] = lit_utf8_peek_next (curr_p);
      saved_positions[code_units_count] = curr_p;
      code_units_count++;
      calculated_length++;

      lit_utf8_incr (&curr_p);
    }

    TEST_ASSERT (length == calculated_length);

    if (code_units_count > 0)
    {
      for (int j = 0; j < test_subiters; j++)
      {
        ecma_length_t index = (ecma_length_t) rand () % code_units_count;
        curr_p = saved_positions[index];
        TEST_ASSERT (lit_utf8_peek_next (curr_p) == code_units[index]);
      }
    }

    curr_p = (lit_utf8_byte_t *) end_p;
    while (curr_p > cesu8_string)
    {
      TEST_ASSERT (code_units_count > 0);
      calculated_length--;
      TEST_ASSERT (code_units[calculated_length] == lit_utf8_peek_prev (curr_p));
      lit_utf8_decr (&curr_p);
    }

    TEST_ASSERT (calculated_length == 0);

    while (curr_p < end_p)
    {
      ecma_char_t code_unit = lit_utf8_read_next (&curr_p);
      TEST_ASSERT (code_unit == code_units[calculated_length]);
      calculated_length++;
    }

    TEST_ASSERT (length == calculated_length);

    while (curr_p > cesu8_string)
    {
      TEST_ASSERT (code_units_count > 0);
      calculated_length--;
      TEST_ASSERT (code_units[calculated_length] == lit_utf8_read_prev (&curr_p));
    }

    TEST_ASSERT (calculated_length == 0);
  }

  /* Overlong-encoded code point */
  lit_utf8_byte_t invalid_cesu8_string_1[] = {0xC0, 0x82};
  TEST_ASSERT (!lit_is_valid_cesu8_string (invalid_cesu8_string_1, sizeof (invalid_cesu8_string_1)));

  /* Overlong-encoded code point */
  lit_utf8_byte_t invalid_cesu8_string_2[] = {0xE0, 0x80, 0x81};
  TEST_ASSERT (!lit_is_valid_cesu8_string (invalid_cesu8_string_2, sizeof (invalid_cesu8_string_2)));

  /* Pair of surrogates: 0xD901 0xDFF0 which encode Unicode character 0x507F0 */
  lit_utf8_byte_t invalid_cesu8_string_3[] = {0xED, 0xA4, 0x81, 0xED, 0xBF, 0xB0};
  TEST_ASSERT (lit_is_valid_cesu8_string (invalid_cesu8_string_3, sizeof (invalid_cesu8_string_3)));

  /* Isolated high surrogate 0xD901 */
  lit_utf8_byte_t valid_utf8_string_1[] = {0xED, 0xA4, 0x81};
  TEST_ASSERT (lit_is_valid_cesu8_string (valid_utf8_string_1, sizeof (valid_utf8_string_1)));

  lit_utf8_byte_t res_buf[3];
  lit_utf8_size_t res_size;

  res_size = lit_code_unit_to_utf8 (0x73, res_buf);
  TEST_ASSERT (res_size == 1);
  TEST_ASSERT (res_buf[0] == 0x73);

  res_size = lit_code_unit_to_utf8 (0x41A, res_buf);
  TEST_ASSERT (res_size == 2);
  TEST_ASSERT (res_buf[0] == 0xD0);
  TEST_ASSERT (res_buf[1] == 0x9A);

  res_size = lit_code_unit_to_utf8 (0xD7FF, res_buf);
  TEST_ASSERT (res_size == 3);
  TEST_ASSERT (res_buf[0] == 0xED);
  TEST_ASSERT (res_buf[1] == 0x9F);
  TEST_ASSERT (res_buf[2] == 0xBF);

  ecma_finalize ();
  jmem_finalize ();

  return 0;
}
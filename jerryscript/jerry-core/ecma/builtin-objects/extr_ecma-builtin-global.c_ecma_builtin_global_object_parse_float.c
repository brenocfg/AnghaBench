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
typedef  scalar_t__ lit_utf8_size_t ;
typedef  scalar_t__ lit_utf8_byte_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_number_t ;
typedef  scalar_t__ ecma_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_NUMBER_MINUS_ONE ; 
 scalar_t__ LIT_CHAR_DOT ; 
 scalar_t__ LIT_CHAR_LOWERCASE_E ; 
 scalar_t__ LIT_CHAR_MINUS ; 
 scalar_t__ LIT_CHAR_PLUS ; 
 scalar_t__ LIT_CHAR_UPPERCASE_E ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_INFINITY_UL ; 
 int /*<<< orphan*/  ecma_make_nan_value () ; 
 int /*<<< orphan*/  ecma_make_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_number_make_infinity (int) ; 
 int /*<<< orphan*/  ecma_string_trim_helper (scalar_t__ const**,scalar_t__*) ; 
 int /*<<< orphan*/  ecma_utf8_string_to_number (scalar_t__ const*,scalar_t__) ; 
 scalar_t__ lit_char_is_decimal_digit (scalar_t__) ; 
 scalar_t__* lit_get_magic_string_utf8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ecma_value_t
ecma_builtin_global_object_parse_float (const lit_utf8_byte_t *string_buff, /**< routine's first argument's
                                                                             *   string buffer */
                                        lit_utf8_size_t string_buff_size) /**< routine's first argument's
                                                                           *   string buffer's size */
{
  if (string_buff_size <= 0)
  {
    return ecma_make_nan_value ();
  }

  const lit_utf8_byte_t *str_curr_p = string_buff;

  /* 2. Remove leading whitespace. */
  ecma_string_trim_helper (&str_curr_p, &string_buff_size);

  const lit_utf8_byte_t *str_end_p = str_curr_p + string_buff_size;
  const lit_utf8_byte_t *start_p = str_curr_p;
  const lit_utf8_byte_t *end_p = str_end_p;

  bool sign = false;
  ecma_char_t current;

  if (str_curr_p < str_end_p)
  {
    /* Check if sign is present. */
    current = *str_curr_p;
    if (current == LIT_CHAR_MINUS)
    {
      sign = true;
    }

    if (current == LIT_CHAR_MINUS || current == LIT_CHAR_PLUS)
    {
      /* Set starting position to be after the sign character. */
      start_p = ++str_curr_p;
    }
  }

  const lit_utf8_byte_t *infinity_str_p = lit_get_magic_string_utf8 (LIT_MAGIC_STRING_INFINITY_UL);
  lit_utf8_byte_t *infinity_str_curr_p = (lit_utf8_byte_t *) infinity_str_p;
  lit_utf8_byte_t *infinity_str_end_p = infinity_str_curr_p + sizeof (*infinity_str_p);

  /* Check if string is equal to "Infinity". */
  while (str_curr_p < str_end_p
         && *str_curr_p++ == *infinity_str_curr_p++)
  {
    if (infinity_str_curr_p == infinity_str_end_p)
    {
      /* String matched Infinity. */
      return ecma_make_number_value (ecma_number_make_infinity (sign));
    }
  }

  /* Reset to starting position. */
  str_curr_p = start_p;

  /* String ended after sign character, or was empty after removing leading whitespace. */
  if (str_curr_p >= str_end_p)
  {
    return ecma_make_nan_value ();
  }

  /* Reset to starting position. */
  str_curr_p = start_p;

  current = *str_curr_p;

  bool has_whole_part = false;
  bool has_fraction_part = false;

  /* Check digits of whole part. */
  if (lit_char_is_decimal_digit (current))
  {
    has_whole_part = true;
    str_curr_p++;

    while (str_curr_p < str_end_p)
    {
      current = *str_curr_p++;
      if (!lit_char_is_decimal_digit (current))
      {
        str_curr_p--;
        break;
      }
    }
  }


  /* Set end position to the end of whole part. */
  end_p = str_curr_p;
  if (str_curr_p < str_end_p)
  {
    current = *str_curr_p;

    /* Check decimal point. */
    if (current == LIT_CHAR_DOT)
    {
      str_curr_p++;

      if (str_curr_p < str_end_p)
      {
        current = *str_curr_p;

        if (lit_char_is_decimal_digit (current))
        {
          has_fraction_part = true;

          /* Check digits of fractional part. */
          while (str_curr_p < str_end_p)
          {
            current = *str_curr_p++;
            if (!lit_char_is_decimal_digit (current))
            {
              str_curr_p--;
              break;
            }
          }

          /* Set end position to end of fraction part. */
          end_p = str_curr_p;
        }
      }
    }
  }


  if (str_curr_p < str_end_p)
  {
    current = *str_curr_p++;
  }

  /* Check exponent. */
  if ((current == LIT_CHAR_LOWERCASE_E || current == LIT_CHAR_UPPERCASE_E)
      && (has_whole_part || has_fraction_part)
      && str_curr_p < str_end_p)
  {
    current = *str_curr_p++;

    /* Check sign of exponent. */
    if ((current == LIT_CHAR_PLUS || current == LIT_CHAR_MINUS)
         && str_curr_p < str_end_p)
    {
      current = *str_curr_p++;
    }

    if (lit_char_is_decimal_digit (current))
    {
      /* Check digits of exponent part. */
      while (str_curr_p < str_end_p)
      {
        current = *str_curr_p++;
        if (!lit_char_is_decimal_digit (current))
        {
          str_curr_p--;
          break;
        }
      }

      /* Set end position to end of exponent part. */
      end_p = str_curr_p;
    }
  }

  /* String did not contain a valid number. */
  if (start_p == end_p)
  {
    return ecma_make_nan_value ();
  }

  /* 5. */
  ecma_number_t ret_num = ecma_utf8_string_to_number (start_p, (lit_utf8_size_t) (end_p - start_p));

  if (sign)
  {
    ret_num *= ECMA_NUMBER_MINUS_ONE;
  }

  return ecma_make_number_value (ret_num);
}
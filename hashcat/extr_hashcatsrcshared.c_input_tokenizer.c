#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int token_cnt; int* attr; int* len; int opt_len; int signatures_cnt; int* len_min; int* len_max; int /*<<< orphan*/  const** buf; int /*<<< orphan*/ * signatures_buf; int /*<<< orphan*/ * sep; int /*<<< orphan*/  const* opt_buf; } ;
typedef  TYPE_1__ token_t ;

/* Variables and functions */
 int PARSER_OK ; 
 int PARSER_SEPARATOR_UNMATCHED ; 
 int PARSER_SIGNATURE_UNMATCHED ; 
 int PARSER_TOKEN_ENCODING ; 
 int PARSER_TOKEN_LENGTH ; 
 int TOKEN_ATTR_FIXED_LENGTH ; 
 int TOKEN_ATTR_OPTIONAL_ROUNDS ; 
 int TOKEN_ATTR_VERIFY_BASE64A ; 
 int TOKEN_ATTR_VERIFY_BASE64B ; 
 int TOKEN_ATTR_VERIFY_BASE64C ; 
 int TOKEN_ATTR_VERIFY_HEX ; 
 int TOKEN_ATTR_VERIFY_LENGTH ; 
 int TOKEN_ATTR_VERIFY_SIGNATURE ; 
 int is_valid_base64a_string (int /*<<< orphan*/  const*,int) ; 
 int is_valid_base64b_string (int /*<<< orphan*/  const*,int) ; 
 int is_valid_base64c_string (int /*<<< orphan*/  const*,int) ; 
 int is_valid_hex_string (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int rounds_count_length (char const*,int) ; 
 scalar_t__ strchr (char const*,int /*<<< orphan*/ ) ; 

int input_tokenizer (const u8 *input_buf, const int input_len, token_t *token)
{
  int len_left = input_len;

  token->buf[0] = input_buf;

  int token_idx;

  for (token_idx = 0; token_idx < token->token_cnt - 1; token_idx++)
  {
    if (token->attr[token_idx] & TOKEN_ATTR_FIXED_LENGTH)
    {
      int len = token->len[token_idx];

      if (len_left < len) return (PARSER_TOKEN_LENGTH);

      token->buf[token_idx + 1] = token->buf[token_idx] + len;

      len_left -= len;
    }
    else
    {
      if (token->attr[token_idx] & TOKEN_ATTR_OPTIONAL_ROUNDS)
      {
        const int len = rounds_count_length ((const char *) token->buf[token_idx], len_left);

        token->opt_buf = token->buf[token_idx];

        token->opt_len = len; // we want an eventual -1 in here, it's used later for verification

        if (len > 0)
        {
          token->buf[token_idx] += len + 1; // +1 = separator

          len_left -= len + 1; // +1 = separator
        }
      }

      const u8 *next_pos = (const u8 *) strchr ((const char *) token->buf[token_idx], token->sep[token_idx]);

      if (next_pos == NULL) return (PARSER_SEPARATOR_UNMATCHED);

      const int len = next_pos - token->buf[token_idx];

      token->len[token_idx] = len;

      token->buf[token_idx + 1] = next_pos + 1; // +1 = separator

      len_left -= len + 1; // +1 = separator
    }
  }

  if (token->attr[token_idx] & TOKEN_ATTR_FIXED_LENGTH)
  {
    int len = token->len[token_idx];

    if (len_left != len) return (PARSER_TOKEN_LENGTH);
  }
  else
  {
    token->len[token_idx] = len_left;
  }

  // verify data

  for (token_idx = 0; token_idx < token->token_cnt; token_idx++)
  {
    if (token->attr[token_idx] & TOKEN_ATTR_VERIFY_SIGNATURE)
    {
      bool matched = false;

      for (int signature_idx = 0; signature_idx < token->signatures_cnt; signature_idx++)
      {
        if (memcmp (token->buf[token_idx], token->signatures_buf[signature_idx], token->len[token_idx]) == 0) matched = true;
      }

      if (matched == false) return (PARSER_SIGNATURE_UNMATCHED);
    }

    if (token->attr[token_idx] & TOKEN_ATTR_VERIFY_LENGTH)
    {
      if (token->len[token_idx] < token->len_min[token_idx]) return (PARSER_TOKEN_LENGTH);
      if (token->len[token_idx] > token->len_max[token_idx]) return (PARSER_TOKEN_LENGTH);
    }

    if (token->attr[token_idx] & TOKEN_ATTR_VERIFY_HEX)
    {
      if (is_valid_hex_string (token->buf[token_idx], token->len[token_idx]) == false) return (PARSER_TOKEN_ENCODING);
    }

    if (token->attr[token_idx] & TOKEN_ATTR_VERIFY_BASE64A)
    {
      if (is_valid_base64a_string (token->buf[token_idx], token->len[token_idx]) == false) return (PARSER_TOKEN_ENCODING);
    }

    if (token->attr[token_idx] & TOKEN_ATTR_VERIFY_BASE64B)
    {
      if (is_valid_base64b_string (token->buf[token_idx], token->len[token_idx]) == false) return (PARSER_TOKEN_ENCODING);
    }

    if (token->attr[token_idx] & TOKEN_ATTR_VERIFY_BASE64C)
    {
      if (is_valid_base64c_string (token->buf[token_idx], token->len[token_idx]) == false) return (PARSER_TOKEN_ENCODING);
    }
  }

  return PARSER_OK;
}
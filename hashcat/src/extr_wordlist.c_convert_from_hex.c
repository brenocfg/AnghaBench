#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int wordlist_autohex_disable; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int opts_type; } ;
typedef  TYPE_2__ hashconfig_t ;
struct TYPE_7__ {TYPE_1__* user_options; TYPE_2__* hashconfig; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 int OPTS_TYPE_PT_HEX ; 
 size_t exec_unhexify (int /*<<< orphan*/  const*,size_t const,int /*<<< orphan*/ *,size_t const) ; 
 char hex_to_u8 (int /*<<< orphan*/  const*) ; 
 int is_hexify (int /*<<< orphan*/  const*,size_t const) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t const) ; 

size_t convert_from_hex (hashcat_ctx_t *hashcat_ctx, char *line_buf, const size_t line_len)
{
  const hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  const user_options_t *user_options = hashcat_ctx->user_options;

  if (line_len & 1) return (line_len); // not in hex

  if (hashconfig->opts_type & OPTS_TYPE_PT_HEX)
  {
    size_t i, j;

    for (i = 0, j = 0; j < line_len; i += 1, j += 2)
    {
      line_buf[i] = hex_to_u8 ((const u8 *) &line_buf[j]);
    }

    memset (line_buf + i, 0, line_len - i);

    return (i);
  }

  if (user_options->wordlist_autohex_disable == false)
  {
    if (is_hexify ((const u8 *) line_buf, line_len) == true)
    {
      const size_t new_len = exec_unhexify ((const u8 *) line_buf, line_len, (u8 *) line_buf, line_len);

      return new_len;
    }
  }

  return (line_len);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_12__ {int opts_type; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_13__ {TYPE_1__* hashconfig; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_14__ {int* cs_buf; int cs_len; } ;
typedef  TYPE_3__ cs_t ;

/* Variables and functions */
 int OPTS_TYPE_PT_HEX ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,...) ; 
 scalar_t__ hex_convert (int /*<<< orphan*/ ) ; 
 int is_valid_hex_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 void* mp_add_cs_buf (TYPE_2__*,int*,int,TYPE_3__*,size_t) ; 

__attribute__((used)) static int mp_gen_css (hashcat_ctx_t *hashcat_ctx, char *mask_buf, size_t mask_len, cs_t *mp_sys, cs_t *mp_usr, cs_t *css_buf, u32 *css_cnt)
{
  const hashconfig_t *hashconfig = hashcat_ctx->hashconfig;

  memset (css_buf, 0, 256 * sizeof (cs_t));

  size_t mask_pos;
  size_t css_pos;

  for (mask_pos = 0, css_pos = 0; mask_pos < mask_len; mask_pos++, css_pos++)
  {
    char p0 = mask_buf[mask_pos];

    if (p0 == '?')
    {
      mask_pos++;

      if (mask_pos == mask_len)
      {
        event_log_error (hashcat_ctx, "Syntax error in mask: %s", mask_buf);

        return -1;
      }

      char p1 = mask_buf[mask_pos];

      u32 chr = (u32) p1;

      int rc = 0;

      switch (p1)
      {
        case 'l': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[0].cs_buf, mp_sys[0].cs_len, css_buf, css_pos);
                  break;
        case 'u': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[1].cs_buf, mp_sys[1].cs_len, css_buf, css_pos);
                  break;
        case 'd': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[2].cs_buf, mp_sys[2].cs_len, css_buf, css_pos);
                  break;
        case 's': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[3].cs_buf, mp_sys[3].cs_len, css_buf, css_pos);
                  break;
        case 'a': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[4].cs_buf, mp_sys[4].cs_len, css_buf, css_pos);
                  break;
        case 'b': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[5].cs_buf, mp_sys[5].cs_len, css_buf, css_pos);
                  break;
        case 'h': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[6].cs_buf, mp_sys[6].cs_len, css_buf, css_pos);
                  break;
        case 'H': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[7].cs_buf, mp_sys[7].cs_len, css_buf, css_pos);
                  break;
        case '1': if (mp_usr[0].cs_len == 0) { event_log_error (hashcat_ctx, "Custom-charset 1 is undefined."); return -1; }
                  rc = mp_add_cs_buf (hashcat_ctx, mp_usr[0].cs_buf, mp_usr[0].cs_len, css_buf, css_pos);
                  break;
        case '2': if (mp_usr[1].cs_len == 0) { event_log_error (hashcat_ctx, "Custom-charset 2 is undefined."); return -1; }
                  rc = mp_add_cs_buf (hashcat_ctx, mp_usr[1].cs_buf, mp_usr[1].cs_len, css_buf, css_pos);
                  break;
        case '3': if (mp_usr[2].cs_len == 0) { event_log_error (hashcat_ctx, "Custom-charset 3 is undefined."); return -1; }
                  rc = mp_add_cs_buf (hashcat_ctx, mp_usr[2].cs_buf, mp_usr[2].cs_len, css_buf, css_pos);
                  break;
        case '4': if (mp_usr[3].cs_len == 0) { event_log_error (hashcat_ctx, "Custom-charset 4 is undefined."); return -1; }
                  rc = mp_add_cs_buf (hashcat_ctx, mp_usr[3].cs_buf, mp_usr[3].cs_len, css_buf, css_pos);
                  break;
        case '?': rc = mp_add_cs_buf (hashcat_ctx, &chr, 1, css_buf, css_pos);
                  break;
        default:  event_log_error (hashcat_ctx, "Syntax error in mask: %s", mask_buf);
                  return -1;
      }

      if (rc == -1) return -1;
    }
    else
    {
      if (hashconfig->opts_type & OPTS_TYPE_PT_HEX)
      {
        mask_pos++;

        // if there is no 2nd hex character, show an error:

        if (mask_pos == mask_len)
        {
          event_log_error (hashcat_ctx, "The hex-charset option expects exactly 2 hexadecimal chars. Failed mask: %s", mask_buf);

          return -1;
        }

        char p1 = mask_buf[mask_pos];

        // if they are not valid hex character, show an error:

        if ((is_valid_hex_char ((u8) p0) == false) || (is_valid_hex_char ((u8) p1) == false))
        {
          event_log_error (hashcat_ctx, "Invalid hex character detected in mask %s", mask_buf);

          return -1;
        }

        u32 chr = 0;

        chr |= (u32) hex_convert ((u8) p1) << 0;
        chr |= (u32) hex_convert ((u8) p0) << 4;

        const int rc = mp_add_cs_buf (hashcat_ctx, &chr, 1, css_buf, css_pos);

        if (rc == -1) return -1;
      }
      else
      {
        u32 chr = (u32) p0;

        const int rc = mp_add_cs_buf (hashcat_ctx, &chr, 1, css_buf, css_pos);

        if (rc == -1) return -1;
      }
    }
  }

  if (css_pos == 0)
  {
    event_log_error (hashcat_ctx, "Invalid mask length (0).");

    return -1;
  }

  *css_cnt = css_pos;

  return 0;
}
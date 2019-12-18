#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  char u32 ;
struct TYPE_10__ {int opts_type; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_11__ {TYPE_1__* hashconfig; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_12__ {char* cs_buf; int cs_len; } ;
typedef  TYPE_3__ cs_t ;

/* Variables and functions */
 int OPTS_TYPE_PT_HEX ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,...) ; 
 scalar_t__ hex_convert (int /*<<< orphan*/ ) ; 
 int is_valid_hex_char (int /*<<< orphan*/ ) ; 
 void* mp_add_cs_buf (TYPE_2__*,char*,int,TYPE_3__*,char) ; 

__attribute__((used)) static int mp_expand (hashcat_ctx_t *hashcat_ctx, const char *in_buf, size_t in_len, cs_t *mp_sys, cs_t *mp_usr, u32 mp_usr_offset, int interpret)
{
  const hashconfig_t *hashconfig = hashcat_ctx->hashconfig;

  size_t in_pos;

  for (in_pos = 0; in_pos < in_len; in_pos++)
  {
    u32 p0 = in_buf[in_pos] & 0xff;

    if (interpret == 1 && p0 == '?')
    {
      in_pos++;

      if (in_pos == in_len)
      {
        event_log_error (hashcat_ctx, "Syntax error in mask: %s", in_buf);

        return -1;
      }

      u32 p1 = in_buf[in_pos] & 0xff;

      int rc = 0;

      switch (p1)
      {
        case 'l': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[0].cs_buf, mp_sys[0].cs_len, mp_usr, mp_usr_offset);
                  break;
        case 'u': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[1].cs_buf, mp_sys[1].cs_len, mp_usr, mp_usr_offset);
                  break;
        case 'd': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[2].cs_buf, mp_sys[2].cs_len, mp_usr, mp_usr_offset);
                  break;
        case 's': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[3].cs_buf, mp_sys[3].cs_len, mp_usr, mp_usr_offset);
                  break;
        case 'a': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[4].cs_buf, mp_sys[4].cs_len, mp_usr, mp_usr_offset);
                  break;
        case 'b': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[5].cs_buf, mp_sys[5].cs_len, mp_usr, mp_usr_offset);
                  break;
        case 'h': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[6].cs_buf, mp_sys[6].cs_len, mp_usr, mp_usr_offset);
                  break;
        case 'H': rc = mp_add_cs_buf (hashcat_ctx, mp_sys[7].cs_buf, mp_sys[7].cs_len, mp_usr, mp_usr_offset);
                  break;
        case '1': if (mp_usr[0].cs_len == 0) { event_log_error (hashcat_ctx, "Custom-charset 1 is undefined."); return -1; }
                  rc = mp_add_cs_buf (hashcat_ctx, mp_usr[0].cs_buf, mp_usr[0].cs_len, mp_usr, mp_usr_offset);
                  break;
        case '2': if (mp_usr[1].cs_len == 0) { event_log_error (hashcat_ctx, "Custom-charset 2 is undefined."); return -1; }
                  rc = mp_add_cs_buf (hashcat_ctx, mp_usr[1].cs_buf, mp_usr[1].cs_len, mp_usr, mp_usr_offset);
                  break;
        case '3': if (mp_usr[2].cs_len == 0) { event_log_error (hashcat_ctx, "Custom-charset 3 is undefined."); return -1; }
                  rc = mp_add_cs_buf (hashcat_ctx, mp_usr[2].cs_buf, mp_usr[2].cs_len, mp_usr, mp_usr_offset);
                  break;
        case '4': if (mp_usr[3].cs_len == 0) { event_log_error (hashcat_ctx, "Custom-charset 4 is undefined."); return -1; }
                  rc = mp_add_cs_buf (hashcat_ctx, mp_usr[3].cs_buf, mp_usr[3].cs_len, mp_usr, mp_usr_offset);
                  break;
        case '?': rc = mp_add_cs_buf (hashcat_ctx, &p0, 1, mp_usr, mp_usr_offset);
                  break;
        default:  event_log_error (hashcat_ctx, "Syntax error in mask: %s", in_buf);
                  return -1;
      }

      if (rc == -1) return -1;
    }
    else
    {
      if (hashconfig->opts_type & OPTS_TYPE_PT_HEX)
      {
        in_pos++;

        if (in_pos == in_len)
        {
          event_log_error (hashcat_ctx, "The hex-charset option expects exactly 2 hexadecimal chars. Failed mask: %s", in_buf);

          return -1;
        }

        u32 p1 = in_buf[in_pos] & 0xff;

        if ((is_valid_hex_char ((u8) p0) == false) || (is_valid_hex_char ((u8) p1) == false))
        {
          event_log_error (hashcat_ctx, "Invalid hex character detected in mask %s", in_buf);

          return -1;
        }

        u32 chr = 0;

        chr  = (u32) hex_convert ((u8) p1) << 0;
        chr |= (u32) hex_convert ((u8) p0) << 4;

        const int rc = mp_add_cs_buf (hashcat_ctx, &chr, 1, mp_usr, mp_usr_offset);

        if (rc == -1) return -1;
      }
      else
      {
        u32 chr = p0;

        const int rc = mp_add_cs_buf (hashcat_ctx, &chr, 1, mp_usr, mp_usr_offset);

        if (rc == -1) return -1;
      }
    }
  }

  return 0;
}
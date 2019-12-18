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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  mp_file ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cs_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_feof (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char const*,char*) ; 
 size_t hc_fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int mp_expand (int /*<<< orphan*/ *,char const*,size_t const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int) ; 
 size_t const strlen (char const*) ; 
 size_t superchop_with_length (char*,size_t const) ; 

__attribute__((used)) static int mp_setup_usr (hashcat_ctx_t *hashcat_ctx, cs_t *mp_sys, cs_t *mp_usr, const char *buf, const u32 userindex)
{
  HCFILE fp;

  if (hc_fopen (&fp, buf, "rb") == false)
  {
    const int rc = mp_expand (hashcat_ctx, buf, strlen (buf), mp_sys, mp_usr, userindex, 1);

    if (rc == -1) return -1;
  }
  else
  {
    char mp_file[1024];

    const size_t nread = hc_fread (mp_file, 1, sizeof (mp_file) - 1, &fp);

    if (!hc_feof (&fp))
    {
      event_log_error (hashcat_ctx, "%s: Custom charset file is too large.", buf);

      hc_fclose (&fp);

      return -1;
    }

    hc_fclose (&fp);

    if (nread == 0)
    {
      event_log_error (hashcat_ctx, "%s: Custom charset file is empty.", buf);

      return -1;
    }

    mp_file[nread] = 0;

    const size_t len = superchop_with_length (mp_file, nread);

    if (len == 0)
    {
      event_log_error (hashcat_ctx, "%s: Custom charset file is corrupted.", buf);

      return -1;
    }

    const int rc = mp_expand (hashcat_ctx, mp_file, len, mp_sys, mp_usr, userindex, 0);

    if (rc == -1) return -1;
  }

  return 0;
}
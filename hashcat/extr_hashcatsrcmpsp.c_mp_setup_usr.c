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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t hc_fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int mp_expand (int /*<<< orphan*/ *,char const*,size_t const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int) ; 
 size_t const strlen (char const*) ; 
 size_t superchop_with_length (char*,size_t const) ; 

__attribute__((used)) static int mp_setup_usr (hashcat_ctx_t *hashcat_ctx, cs_t *mp_sys, cs_t *mp_usr, const char *buf, const u32 userindex)
{
  FILE *fp = fopen (buf, "rb");

  if (fp == NULL) // feof() in case if file is empty
  {
    const int rc = mp_expand (hashcat_ctx, buf, strlen (buf), mp_sys, mp_usr, userindex, 1);

    if (rc == -1) return -1;
  }
  else
  {
    char mp_file[1024];

    const size_t nread = hc_fread (mp_file, 1, sizeof (mp_file) - 1, fp);

    if (!feof (fp))
    {
      event_log_error (hashcat_ctx, "%s: Custom charset file is too large.", buf);

      fclose (fp);

      return -1;
    }

    fclose (fp);

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
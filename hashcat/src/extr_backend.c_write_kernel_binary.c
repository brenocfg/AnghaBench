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
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_fflush (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  hc_fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int hc_lockfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool write_kernel_binary (hashcat_ctx_t *hashcat_ctx, char *kernel_file, char *binary, size_t binary_size)
{
  if (binary_size > 0)
  {
    HCFILE fp;

    if (hc_fopen (&fp, kernel_file, "wb") == false)
    {
      event_log_error (hashcat_ctx, "%s: %s", kernel_file, strerror (errno));

      return false;
    }

    if (hc_lockfile (&fp) == -1)
    {
      hc_fclose (&fp);

      event_log_error (hashcat_ctx, "%s: %s", kernel_file, strerror (errno));

      return false;
    }

    hc_fwrite (binary, sizeof (char), binary_size, &fp);

    hc_fflush (&fp);

    hc_fclose (&fp);
  }

  return true;
}
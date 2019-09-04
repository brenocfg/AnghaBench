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
typedef  int u32 ;
typedef  scalar_t__ time_t ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t hc_fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int) ; 
 int snprintf (char*,int,char*,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool read_kernel_binary (hashcat_ctx_t *hashcat_ctx, const char *kernel_file, size_t *kernel_lengths, char **kernel_sources, const bool force_recompile)
{
  FILE *fp = fopen (kernel_file, "rb");

  if (fp != NULL)
  {
    struct stat st;

    if (stat (kernel_file, &st))
    {
      fclose (fp);

      return false;
    }

    #define EXTRASZ 100

    char *buf = (char *) hcmalloc (st.st_size + 1 + EXTRASZ);

    size_t num_read = hc_fread (buf, sizeof (char), st.st_size, fp);

    fclose (fp);

    if (num_read != (size_t) st.st_size)
    {
      event_log_error (hashcat_ctx, "%s: %s", kernel_file, strerror (errno));

      hcfree (buf);

      return false;
    }

    buf[st.st_size] = 0;

    if (force_recompile == true)
    {
      // this adds some hopefully unique data to the opencl kernel source
      // the effect should be that opencl kernel compiler caching see this as new "uncached" source
      // we have to do this since they do not check for the changes only in the #include source

      time_t tlog = time (NULL);

      const int extra_len = snprintf (buf + st.st_size, EXTRASZ, "\n//%u\n", (u32) tlog);

      st.st_size += extra_len;
    }

    kernel_lengths[0] = (size_t) st.st_size;

    kernel_sources[0] = buf;
  }
  else
  {
    event_log_error (hashcat_ctx, "%s: %s", kernel_file, strerror (errno));

    return false;
  }

  return true;
}
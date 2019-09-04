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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  brain_logging (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

u32 brain_auth_challenge (void)
{
  srand (time (NULL));

  u32 val = rand (); // just a fallback value

  #if defined (_WIN)

  // from

  HCRYPTPROV hCryptProv;

  if (CryptAcquireContext (&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0) == true)
  {
    if (CryptGenRandom (hCryptProv, sizeof (val), (BYTE *) &val) == true)
    {
      // all good
    }
    else
    {
      brain_logging (stderr, 0, "CryptGenRandom: %d\n", (int) GetLastError ());

      return val;
    }

    CryptReleaseContext (hCryptProv, 0);
  }
  else
  {
    brain_logging (stderr, 0, "CryptAcquireContext: %d\n", (int) GetLastError ());

    return val;
  }

  #else

  static const char *urandom = "/dev/urandom";

  FILE *fd = fopen (urandom, "rb");

  if (fd == NULL)
  {
    brain_logging (stderr, 0, "%s: %s\n", urandom, strerror (errno));

    return val;
  }

  if (fread (&val, sizeof (val), 1, fd) != 1)
  {
    brain_logging (stderr, 0, "%s: %s\n", urandom, strerror (errno));

    fclose (fd);

    return val;
  }

  fclose (fd);

  #endif

  return val;
}
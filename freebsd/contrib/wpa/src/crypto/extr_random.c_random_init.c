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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  GRND_NONBLOCK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  eloop_register_read_sock (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ getrandom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ open (char*,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_strdup (char const*) ; 
 int /*<<< orphan*/ * random_entropy_file ; 
 scalar_t__ random_fd ; 
 int /*<<< orphan*/  random_read_entropy () ; 
 int /*<<< orphan*/  random_read_fd ; 
 int /*<<< orphan*/  random_write_entropy () ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

void random_init(const char *entropy_file)
{
	os_free(random_entropy_file);
	if (entropy_file)
		random_entropy_file = os_strdup(entropy_file);
	else
		random_entropy_file = NULL;
	random_read_entropy();

#ifdef __linux__
	if (random_fd >= 0)
		return;

#ifdef CONFIG_GETRANDOM
	{
		u8 dummy;

		if (getrandom(&dummy, 0, GRND_NONBLOCK) == 0 ||
		    errno != ENOSYS) {
			wpa_printf(MSG_DEBUG,
				   "random: getrandom() support available");
			return;
		}
	}
#endif /* CONFIG_GETRANDOM */

	random_fd = open("/dev/random", O_RDONLY | O_NONBLOCK);
	if (random_fd < 0) {
		wpa_printf(MSG_ERROR, "random: Cannot open /dev/random: %s",
			   strerror(errno));
		return;
	}
	wpa_printf(MSG_DEBUG, "random: Trying to read entropy from "
		   "/dev/random");

	eloop_register_read_sock(random_fd, random_read_fd, NULL, NULL);
#endif /* __linux__ */

	random_write_entropy();
}
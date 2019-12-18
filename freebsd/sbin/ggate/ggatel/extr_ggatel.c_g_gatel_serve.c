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
struct g_gate_ctl_io {size_t gctl_length; int gctl_error; int gctl_cmd; int /*<<< orphan*/  gctl_offset; int /*<<< orphan*/ * gctl_data; int /*<<< orphan*/  gctl_unit; int /*<<< orphan*/  gctl_version; } ;

/* Variables and functions */
#define  BIO_DELETE 133 
#define  BIO_READ 132 
#define  BIO_WRITE 131 
#define  ECANCELED 130 
#define  ENOMEM 129 
#define  ENXIO 128 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  G_GATE_CMD_DONE ; 
 int /*<<< orphan*/  G_GATE_CMD_START ; 
 int /*<<< orphan*/  G_GATE_CTL_NAME ; 
 int /*<<< orphan*/  G_GATE_VERSION ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_gate_close_device () ; 
 int /*<<< orphan*/  g_gate_destroy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_gate_ioctl (int /*<<< orphan*/ ,struct g_gate_ctl_io*) ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_gate_verbose ; 
 int /*<<< orphan*/  g_gate_xlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int pread (int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int pwrite (int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 void* realloc (int /*<<< orphan*/ *,size_t) ; 
 size_t sectorsize ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  unit ; 

__attribute__((used)) static void
g_gatel_serve(int fd)
{
	struct g_gate_ctl_io ggio;
	size_t bsize;

	if (g_gate_verbose == 0) {
		if (daemon(0, 0) == -1) {
			g_gate_destroy(unit, 1);
			err(EXIT_FAILURE, "Cannot daemonize");
		}
	}
	g_gate_log(LOG_DEBUG, "Worker created: %u.", getpid());
	ggio.gctl_version = G_GATE_VERSION;
	ggio.gctl_unit = unit;
	bsize = sectorsize;
	ggio.gctl_data = malloc(bsize);
	for (;;) {
		int error;
once_again:
		ggio.gctl_length = bsize;
		ggio.gctl_error = 0;
		g_gate_ioctl(G_GATE_CMD_START, &ggio);
		error = ggio.gctl_error;
		switch (error) {
		case 0:
			break;
		case ECANCELED:
			/* Exit gracefully. */
			free(ggio.gctl_data);
			g_gate_close_device();
			close(fd);
			exit(EXIT_SUCCESS);
		case ENOMEM:
			/* Buffer too small. */
			assert(ggio.gctl_cmd == BIO_DELETE ||
			    ggio.gctl_cmd == BIO_WRITE);
			ggio.gctl_data = realloc(ggio.gctl_data,
			    ggio.gctl_length);
			if (ggio.gctl_data != NULL) {
				bsize = ggio.gctl_length;
				goto once_again;
			}
			/* FALLTHROUGH */
		case ENXIO:
		default:
			g_gate_xlog("ioctl(/dev/%s): %s.", G_GATE_CTL_NAME,
			    strerror(error));
		}

		error = 0;
		switch (ggio.gctl_cmd) {
		case BIO_READ:
			if ((size_t)ggio.gctl_length > bsize) {
				ggio.gctl_data = realloc(ggio.gctl_data,
				    ggio.gctl_length);
				if (ggio.gctl_data != NULL)
					bsize = ggio.gctl_length;
				else
					error = ENOMEM;
			}
			if (error == 0) {
				if (pread(fd, ggio.gctl_data, ggio.gctl_length,
				    ggio.gctl_offset) == -1) {
					error = errno;
				}
			}
			break;
		case BIO_DELETE:
		case BIO_WRITE:
			if (pwrite(fd, ggio.gctl_data, ggio.gctl_length,
			    ggio.gctl_offset) == -1) {
				error = errno;
			}
			break;
		default:
			error = EOPNOTSUPP;
		}

		ggio.gctl_error = error;
		g_gate_ioctl(G_GATE_CMD_DONE, &ggio);
	}
}
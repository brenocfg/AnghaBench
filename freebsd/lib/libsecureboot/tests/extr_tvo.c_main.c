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
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  DebugVe ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* Skip ; 
 int /*<<< orphan*/  VE_GUESS ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  fingerprint_info_add (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read_file (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strstr (char*,char*) ; 
 char* ve_error_get () ; 
 int /*<<< orphan*/  ve_pcr_updating_set (int) ; 
 int /*<<< orphan*/  ve_self_tests () ; 
 int ve_trust_add (char*) ; 
 int ve_trust_init () ; 
 int vectx_close (void*) ; 
 size_t vectx_lseek (void*,int,int /*<<< orphan*/ ) ; 
 void* vectx_open (int,char*,size_t,struct stat*,int*) ; 
 size_t vectx_read (void*,char*,int) ; 
 scalar_t__ verify_asc (char*,int) ; 
 int verify_file (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verify_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_pcr_export () ; 
 scalar_t__ verify_sig (char*,int) ; 

int
main(int argc, char *argv[])
{
	int n;
	int fd;
	int c;
	int Vflag;
	char *cp;
	char *prefix;

	prefix = NULL;
	Skip = NULL;

	n = ve_trust_init();
	printf("Trust %d\n", n);
	Vflag = 0;

	while ((c = getopt(argc, argv, "dp:s:T:V")) != -1) {
		switch (c) {
		case 'd':
			DebugVe++;
			break;
		case 'p':
			prefix = optarg;
			break;
		case 's':
			Skip = optarg;
			break;
		case 'T':
			n = ve_trust_add(optarg);
			printf("Local trust %s: %d\n", optarg, n);
			break;
		case 'V':
			Vflag = 1;
			break;
		default:
			errx(1, "unknown option: -%c", c);
			break;
		}
	}

#ifdef VE_PCR_SUPPORT
	ve_pcr_updating_set(1);
#endif
	ve_self_tests();

	for ( ; optind < argc; optind++) {
		if (Vflag) {
			/*
			 * Simulate what loader does.
			 * verify_file should "just work"
			 */
			fd = open(argv[optind], O_RDONLY);
			if (fd > 0) {
				/*
				 * See if verify_file is happy
				 */
				int x;

				x = verify_file(fd, argv[optind], 0, VE_GUESS);
				printf("verify_file(%s) = %d\n", argv[optind], x);
				close(fd);
			}
			continue;
		}
#ifdef VE_OPENPGP_SUPPORT
		if (strstr(argv[optind], "asc")) {
			cp = (char *)verify_asc(argv[optind], 1);
			if (cp) {
				printf("Verified: %s: %.28s...\n",
				    argv[optind], cp);
				fingerprint_info_add(argv[optind],
				    prefix, Skip, cp, NULL);
			} else {
				fprintf(stderr, "%s: %s\n",
				    argv[optind], ve_error_get());
			}
		} else
#endif
		if (strstr(argv[optind], "sig")) {
			cp = (char *)verify_sig(argv[optind], 1);
			if (cp) {
				printf("Verified: %s: %.28s...\n",
				    argv[optind], cp);
				fingerprint_info_add(argv[optind],
				    prefix, Skip, cp, NULL);
			} else {
				fprintf(stderr, "%s: %s\n",
				    argv[optind], ve_error_get());
			}
		} else if (strstr(argv[optind], "manifest")) {
			cp = (char *)read_file(argv[optind], NULL);
			if (cp) {
				fingerprint_info_add(argv[optind],
				    prefix, Skip, cp, NULL);
			}
		} else {
			fd = verify_open(argv[optind], O_RDONLY);
			printf("verify_open(%s) = %d %s\n", argv[optind], fd,
			    (fd < 0) ? ve_error_get() : "");
			if (fd > 0) {
				/*
				 * Check that vectx_* can also verify the file.
				 */
				void *vp;
				char buf[BUFSIZ];
				struct stat st;
				int error;
				size_t off, n;

				fstat(fd, &st);
				lseek(fd, 0, SEEK_SET);
				off = st.st_size % 512;
				vp = vectx_open(fd, argv[optind], off,
				    &st, &error);
				if (!vp) {
					printf("vectx_open(%s) failed: %d %s\n",
					    argv[optind], error,
					    ve_error_get());
				} else {
					off = vectx_lseek(vp,
					    (st.st_size % 1024), SEEK_SET);

					if (off < st.st_size) {
						n = vectx_read(vp, buf,
						    sizeof(buf));
						if (n > 0)
							off += n;
					}
					off = vectx_lseek(vp, 0, SEEK_END);
					/* repeating that should be harmless */
					off = vectx_lseek(vp, 0, SEEK_END);
					error = vectx_close(vp);
					if (error) {
						printf("vectx_close(%s) == %d %s\n",
						    argv[optind], error,
						    ve_error_get());
					} else {
						printf("vectx_close: Verified: %s\n",
						    argv[optind]);
					}
				}
				close(fd);
			}
		}
	}
#ifdef VE_PCR_SUPPORT
	verify_pcr_export();
	printf("pcr=%s\n", getenv("loader.ve.pcr"));
#endif
	return (0);
}
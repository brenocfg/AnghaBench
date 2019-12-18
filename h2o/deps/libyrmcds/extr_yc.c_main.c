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
typedef  scalar_t__ yrmcds_error ;
typedef  int /*<<< orphan*/  yrmcds ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERROR (scalar_t__) ; 
 size_t DEFAULT_COMPRESS ; 
 int /*<<< orphan*/  DEFAULT_PORT ; 
 char* DEFAULT_SERVER ; 
 scalar_t__ YRMCDS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  add () ; 
 int /*<<< orphan*/  append () ; 
 int atoi (char*) ; 
 int debug ; 
 int /*<<< orphan*/  decr () ; 
 int /*<<< orphan*/  delete () ; 
 int /*<<< orphan*/  do_cmd (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  flush () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gat () ; 
 int /*<<< orphan*/  gatk () ; 
 int /*<<< orphan*/  get () ; 
 int /*<<< orphan*/  getk () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  incr () ; 
 int /*<<< orphan*/  keys () ; 
 int /*<<< orphan*/  lag () ; 
 int /*<<< orphan*/  lagk () ; 
 int /*<<< orphan*/  lock () ; 
 int /*<<< orphan*/  noop () ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  prepend () ; 
 int quiet ; 
 int /*<<< orphan*/  quit () ; 
 int /*<<< orphan*/  rau () ; 
 int /*<<< orphan*/  replace () ; 
 int /*<<< orphan*/  set () ; 
 int /*<<< orphan*/  stat () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  touch () ; 
 int /*<<< orphan*/  unlock () ; 
 int /*<<< orphan*/  unlockall () ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  version () ; 
 int /*<<< orphan*/  yrmcds_close (int /*<<< orphan*/ *) ; 
 scalar_t__ yrmcds_connect (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ yrmcds_set_compression (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ yrmcds_text_mode (int /*<<< orphan*/ *) ; 

int main(int argc, char** argv) {
    const char* server = DEFAULT_SERVER;
    uint16_t port = DEFAULT_PORT;
    size_t compression = DEFAULT_COMPRESS;
    int text_mode = 0;

    while( 1 ) {
        int n;
        int c = getopt(argc, argv, "s:p:c:dtqvh");
        if( c == -1 ) break;
        switch( c ) {
        case 's':
            server = optarg;
            break;
        case 'p':
            n = atoi(optarg);
            if( n <= 0 || n > 65535 ) {
                fprintf(stderr, "Invalid TCP port.\n");
                return 1;
            }
            port = (uint16_t)n;
            break;
        case 'c':
            n = atoi(optarg);
            if( n <= 0 ) {
                fprintf(stderr, "Invalid compression thoreshold.\n");
                return 1;
            }
            compression = (size_t)n;
            break;
        case 'd':
            debug = 1;
            break;
        case 't':
            text_mode = 1;
            break;
        case 'q':
            quiet = 1;
            break;
        case 'v':
            version();
            return 0;
        case 'h':
            usage();
            return 0;
        default:
            return 1;
        }
    }

    if( optind == argc ) {
        usage();
        return 0;
    }

    const char* cmd = argv[optind];
    argc -= optind + 1;
    argv += optind + 1;

    yrmcds s[1];
    yrmcds_error e = yrmcds_connect(s, server, port);
    CHECK_ERROR(e);
    if( text_mode ) {
        e = yrmcds_text_mode(s);
        CHECK_ERROR(e);
    }
    e = yrmcds_set_compression(s, compression);
    if( e != 0 && e != YRMCDS_NOT_IMPLEMENTED ) {
        yrmcds_close(s);
        CHECK_ERROR(e);
    }

    int ret = 1;
#define do_cmd(name)                            \
    if( strcmp(cmd, #name) == 0 )  {            \
        ret = cmd_##name(argc, argv, s);        \
            goto OUT;                           \
    }

    do_cmd(noop);
    do_cmd(get);
    do_cmd(getk);
    do_cmd(gat);
    do_cmd(gatk);
    do_cmd(lag);
    do_cmd(lagk);
    do_cmd(touch);
    do_cmd(set);
    do_cmd(replace);
    do_cmd(add);
    do_cmd(rau);
    do_cmd(incr);
    do_cmd(decr);
    do_cmd(append);
    do_cmd(prepend);
    do_cmd(delete);
    do_cmd(lock);
    do_cmd(unlock);
    do_cmd(unlockall);
    do_cmd(flush);
    do_cmd(stat);
    do_cmd(keys);
    do_cmd(version);
    do_cmd(quit);

    fprintf(stderr, "No such command: %s\n", cmd);

  OUT:
    yrmcds_close(s);
    return ret;
}
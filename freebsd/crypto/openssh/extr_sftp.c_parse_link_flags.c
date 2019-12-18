__attribute__((used)) static int
parse_link_flags(const char *cmd, char **argv, int argc, int *sflag)
{
	extern int opterr, optind, optopt, optreset;
	int ch;

	optind = optreset = 1;
	opterr = 0;

	*sflag = 0;
	while ((ch = getopt(argc, argv, "s")) != -1) {
		switch (ch) {
		case 's':
			*sflag = 1;
			break;
		default:
			error("%s: Invalid flag -%c", cmd, optopt);
			return -1;
		}
	}

	return optind;
}
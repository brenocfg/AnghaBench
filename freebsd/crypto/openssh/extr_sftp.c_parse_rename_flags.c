__attribute__((used)) static int
parse_rename_flags(const char *cmd, char **argv, int argc, int *lflag)
{
	extern int opterr, optind, optopt, optreset;
	int ch;

	optind = optreset = 1;
	opterr = 0;

	*lflag = 0;
	while ((ch = getopt(argc, argv, "l")) != -1) {
		switch (ch) {
		case 'l':
			*lflag = 1;
			break;
		default:
			error("%s: Invalid flag -%c", cmd, optopt);
			return -1;
		}
	}

	return optind;
}
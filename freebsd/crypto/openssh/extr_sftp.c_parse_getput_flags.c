__attribute__((used)) static int
parse_getput_flags(const char *cmd, char **argv, int argc,
    int *aflag, int *fflag, int *pflag, int *rflag)
{
	extern int opterr, optind, optopt, optreset;
	int ch;

	optind = optreset = 1;
	opterr = 0;

	*aflag = *fflag = *rflag = *pflag = 0;
	while ((ch = getopt(argc, argv, "afPpRr")) != -1) {
		switch (ch) {
		case 'a':
			*aflag = 1;
			break;
		case 'f':
			*fflag = 1;
			break;
		case 'p':
		case 'P':
			*pflag = 1;
			break;
		case 'r':
		case 'R':
			*rflag = 1;
			break;
		default:
			error("%s: Invalid flag -%c", cmd, optopt);
			return -1;
		}
	}

	return optind;
}
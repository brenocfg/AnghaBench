__attribute__((used)) static int
parse_df_flags(const char *cmd, char **argv, int argc, int *hflag, int *iflag)
{
	extern int opterr, optind, optopt, optreset;
	int ch;

	optind = optreset = 1;
	opterr = 0;

	*hflag = *iflag = 0;
	while ((ch = getopt(argc, argv, "hi")) != -1) {
		switch (ch) {
		case 'h':
			*hflag = 1;
			break;
		case 'i':
			*iflag = 1;
			break;
		default:
			error("%s: Invalid flag -%c", cmd, optopt);
			return -1;
		}
	}

	return optind;
}